#include "draw.h"
#include <SFML/Graphics.hpp>
#include "../Lib/functions.h"
#include "../Lib/variables.h"
#include "../Value/bignumbervalue.h"
#include "../Value/arrayvalue.h"
#include "../Value/stringvalue.h"
#include "../Exception/argumentsmismatchexception.h"
#include <iostream>

namespace{
    enum class Keys{
        ESCAPE,
        UP,
        DOWN,
        LEFT,
        RIGHT,
        SPACE
    };
    const sf::Color defaultColor = sf::Color(255, 255, 255);
    const int RGB = 255;
    const int defaultHeight = 480;
    const int defaultWidth = 640;
    const int defaultLimit = 100;
    const std::string defaultTitle = "SlavaScript in window";
    sf::RenderWindow window;
    sf::Color color = defaultColor;
    int correctColor(double alpha){
        if (alpha <  0) return 0;
        if (alpha > 255) return 255;
        return int(alpha);
    }
    class Window : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            int siz = values.size();
            if (siz < 1 || siz > 3) throw new ArgumentsMismatchException("One or two or three arguments expected");
            switch(siz){
                case (1) : {
                    window.create(sf::VideoMode(defaultWidth, defaultHeight), values[0] -> asString());
                    break;
                }
                case (2): {
                    window.create(sf::VideoMode(values[0] -> asDouble(), values[1] -> asDouble()), defaultTitle);
                    break;
                }
                case (3): {
                    window.create(sf::VideoMode(values[1] -> asDouble(), values[2] -> asDouble()), values[0] -> asString());
                    break;
                }
            }
            window.setFramerateLimit(defaultLimit);
            return new BigNumberValue(0);
        }
    };
    class Color : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            int siz = values.size();
            if (siz > 3) throw new ArgumentsMismatchException("One or two or three arguments expected");
            if (!siz) color = defaultColor;
            else{
                if (siz == 1){
                    int colo = values[0] -> asDouble();
                    color = sf::Color(colo / (RGB + 1) / (RGB + 1), colo / (RGB + 1) % (RGB + 1), colo % (RGB + 1));
                }
                else{
                    int red = correctColor(values[0] -> asDouble());
                    int green = correctColor(values[1] -> asDouble());
                    if (siz == 2) color = sf::Color(red, green, RGB);
                    else{
                        int blue = correctColor(values[2] -> asDouble());
                        color = sf::Color(red, green, blue);
                    }
                }
            }
            return new BigNumberValue(0);
        }
    };
    class Line : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 4) throw new ArgumentsMismatchException("Four arguments expected");
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = sf::Vector2f(values[0] -> asDouble(), values[1] -> asDouble());
            line[0].color = color;
            line[1].position = sf::Vector2f(values[2] -> asDouble(), values[3] -> asDouble());
            line[1].color = color;
            window.draw(line);
            return new BigNumberValue(0);
        }
    };
    class Rect : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 4) throw new ArgumentsMismatchException("Four arguments expected");
            sf::RectangleShape rect;
            rect.setSize(sf::Vector2f(values[2] -> asDouble(), values[3] -> asDouble()));
            rect.setPosition(values[0] -> asDouble(), values[1] -> asDouble());
            rect.setOutlineThickness(5);
            rect.setOutlineColor(sf::Color::Black);
            window.draw(rect);
            return new BigNumberValue(0);
        }
    };
    class Frect : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 4) throw new ArgumentsMismatchException("Four arguments expected");
            sf::RectangleShape rect;
            rect.setSize(sf::Vector2f(values[2] -> asDouble(), values[3] -> asDouble()));
            rect.setPosition(values[0] -> asDouble(), values[1] -> asDouble());
            rect.setFillColor(color);
            window.draw(rect);
            return new BigNumberValue(0);
        }
    };
    class Circle : public Function{
        Value* execute(std::vector<Value*> values){
            if (values.size() != 3) throw new ArgumentsMismatchException("Three arguments expected");
            sf::CircleShape cricle(values[2] -> asDouble());
            cricle.setPosition(values[0] -> asDouble(), values[1] -> asDouble());
            window.draw(cricle);
            return new BigNumberValue(0);
        }
    };
    class Fcircle : public Function{
        Value* execute(std::vector<Value*> values){
            if (values.size() != 3) throw new ArgumentsMismatchException("Three arguments expected");
            sf::CircleShape cricle(values[2] -> asDouble());
            cricle.setPosition(values[0] -> asDouble(), values[1] -> asDouble());
            cricle.setFillColor(color);
            window.draw(cricle);
            return new BigNumberValue(0);
        }
    };
    class Repaint : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size()) throw new ArgumentsMismatchException("Zero arguments expected");
            sf::Event event;
            while (window.pollEvent(event)) if (event.type == sf::Event::Closed) window.close();
            //draw(*window);
            window.display();
        }
    };
    class Clear : public Function{
    public:
        Value* execute(std::vector<Value*> values){
 //           std::cout << "In clear size of vector : " << shapes.size() << "\tand : " << sizeof(*window) << std::endl;
            if (values.size()) throw new ArgumentsMismatchException("Zero arguments expected");
            sf::Event event;
            while (window.pollEvent(event)) if (event.type == sf::Event::Closed) window.close();
            window.clear();
//            for (int i = 0; i < shapes.size(); ++i) delete shapes[i];
//            shapes.clear();
        }
    };
    class FrameLimit : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() > 1) throw new ArgumentsMismatchException("Zero or one arguments expected");
            if (values.size()) window.setFramerateLimit(values[0] -> asDouble());
            else window.setFramerateLimit(defaultLimit);
        }
    };
    class KeyPressed : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size()) throw new ArgumentsMismatchException("Zero arguments expected");
            sf::Event event;
            while (window.pollEvent(event)){
                if (event.type == sf::Event::Closed) window.close();
                if (event.type == sf::Event::KeyPressed){
                    if (event.key.code == sf::Keyboard::Escape) return new BigNumberValue(int(Keys::ESCAPE));
                    if (event.key.code == sf::Keyboard::Up) return new BigNumberValue(int(Keys::UP));
                    if (event.key.code == sf::Keyboard::Down) return new BigNumberValue(int(Keys::DOWN));
                    if (event.key.code == sf::Keyboard::Left) return new BigNumberValue(int(Keys::LEFT));
                    if (event.key.code == sf::Keyboard::Right) return new BigNumberValue(int(Keys::RIGHT));
                    if (event.key.code == sf::Keyboard::Space) return new BigNumberValue(int(Keys::SPACE));
                }
            }
            return new BigNumberValue(-1);
        }
    };
    class MouseHover : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size()) throw new ArgumentsMismatchException("Zero arguments expected");
            ArrayValue* arr = new ArrayValue(2);
            sf::Vector2i pixesPos = sf::Mouse::getPosition(window);
            sf::Vector2f pos = window.mapPixelToCoords(pixesPos);
            arr -> set(0, new BigNumberValue(pos.x));
            arr -> set(1, new BigNumberValue(pos.y));
            sf::Event event;
            while (window.pollEvent(event)) if (event.type == sf::Event::Closed) window.close();
            return arr;
        }
    };
    class Close : public Function{
    public:
        Value* execute(std::vector<Value*> values){
             if (values.size()) throw new ArgumentsMismatchException("Zero arguments expected");
             window.close();
        }
    };
}

void Draw::initConstants(){
    Variables::set("KB_ESCAPE", new BigNumberValue(int(Keys::ESCAPE)));
    Variables::set("KB_UP", new BigNumberValue(int(Keys::UP)));
    Variables::set("KB_DOWN", new BigNumberValue(int(Keys::DOWN)));
    Variables::set("KB_LEFT", new BigNumberValue(int(Keys::LEFT)));
    Variables::set("KB_RIGHT", new BigNumberValue(int(Keys::RIGHT)));
    Variables::set("KB_SPACE", new BigNumberValue(int(Keys::SPACE)));
}

void Draw::initFunctions(){
    Functions::set("window", new Window());
    Functions::set("color", new Color());
    Functions::set("line", new Line());
    Functions::set("rect", new Rect());
    Functions::set("frect", new Frect());
    Functions::set("circle", new Circle());
    Functions::set("fcircle", new Fcircle);
    Functions::set("repaint", new Repaint());
    Functions::set("clear", new Clear());
    Functions::set("framelimit", new FrameLimit());
    Functions::set("keypressed", new KeyPressed());
    Functions::set("mousehover", new MouseHover());
    Functions::set("close", new Close());
}
