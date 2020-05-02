#include "draw.h"
#include <SFML/Graphics.hpp>
#include "../Lib/functions.h"
#include "../Lib/variables.h"
#include "../Lib/bignumber.h"
#include "../Lib/array.h"
#include "../Lib/string.h"
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
                    window.create(sf::VideoMode(defaultWidth, defaultHeight), values[0] -> getString());
                    break;
                }
                case (2): {
                    window.create(sf::VideoMode(values[0] -> getDouble(), values[1] -> getDouble()), defaultTitle);
                    break;
                }
                case (3): {
                    window.create(sf::VideoMode(values[1] -> getDouble(), values[2] -> getDouble()), values[0] -> getString());
                    break;
                }
            }
            window.setFramerateLimit(defaultLimit);
            return new BigNumber(0);
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
                    int colo = values[0] -> getDouble();
                    color = sf::Color(colo / (RGB + 1) / (RGB + 1), colo / (RGB + 1) % (RGB + 1), colo % (RGB + 1));
                }
                else{
                    int red = correctColor(values[0] -> getDouble());
                    int green = correctColor(values[1] -> getDouble());
                    if (siz == 2) color = sf::Color(red, green, RGB);
                    else{
                        int blue = correctColor(values[2] -> getDouble());
                        color = sf::Color(red, green, blue);
                    }
                }
            }
            return new BigNumber(0);
        }
    };
    class Line : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 4) throw new ArgumentsMismatchException("Four arguments expected");
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = sf::Vector2f(values[0] -> getDouble(), values[1] -> getDouble());
            line[0].color = color;
            line[1].position = sf::Vector2f(values[2] -> getDouble(), values[3] -> getDouble());
            line[1].color = color;
            window.draw(line);
            return new BigNumber(0);
        }
    };
    class Rect : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 4) throw new ArgumentsMismatchException("Four arguments expected");
            sf::RectangleShape rect;
            rect.setSize(sf::Vector2f(values[2] -> getDouble(), values[3] -> getDouble()));
            rect.setPosition(values[0] -> getDouble(), values[1] -> getDouble());
            rect.setOutlineThickness(5);
            rect.setOutlineColor(sf::Color::Black);
            window.draw(rect);
            return new BigNumber(0);
        }
    };
    class Frect : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 4) throw new ArgumentsMismatchException("Four arguments expected");
            sf::RectangleShape rect;
            rect.setSize(sf::Vector2f(values[2] -> getDouble(), values[3] -> getDouble()));
            rect.setPosition(values[0] -> getDouble(), values[1] -> getDouble());
            rect.setFillColor(color);
            window.draw(rect);
            return new BigNumber(0);
        }
    };
    class Circle : public Function{
        Value* execute(std::vector<Value*> values){
            if (values.size() != 3) throw new ArgumentsMismatchException("Three arguments expected");
            sf::CircleShape cricle(values[2] -> getDouble());
            cricle.setPosition(values[0] -> getDouble(), values[1] -> getDouble());
            window.draw(cricle);
            return new BigNumber(0);
        }
    };
    class Fcircle : public Function{
        Value* execute(std::vector<Value*> values){
            if (values.size() != 3) throw new ArgumentsMismatchException("Three arguments expected");
            sf::CircleShape cricle(values[2] -> getDouble());
            cricle.setPosition(values[0] -> getDouble(), values[1] -> getDouble());
            cricle.setFillColor(color);
            window.draw(cricle);
            return new BigNumber(0);
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
            if (values.size()) window.setFramerateLimit(values[0] -> getDouble());
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
                    if (event.key.code == sf::Keyboard::Escape) return new BigNumber(int(Keys::ESCAPE));
                    if (event.key.code == sf::Keyboard::Up) return new BigNumber(int(Keys::UP));
                    if (event.key.code == sf::Keyboard::Down) return new BigNumber(int(Keys::DOWN));
                    if (event.key.code == sf::Keyboard::Left) return new BigNumber(int(Keys::LEFT));
                    if (event.key.code == sf::Keyboard::Right) return new BigNumber(int(Keys::RIGHT));
                    if (event.key.code == sf::Keyboard::Space) return new BigNumber(int(Keys::SPACE));
                }
            }
            return new BigNumber(-1);
        }
    };
    class MouseHover : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size()) throw new ArgumentsMismatchException("Zero arguments expected");
            Array* arr = new Array(2);
            sf::Vector2i pixesPos = sf::Mouse::getPosition(window);
            sf::Vector2f pos = window.mapPixelToCoords(pixesPos);
            arr -> set(0, new BigNumber(pos.x));
            arr -> set(1, new BigNumber(pos.y));
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
    Variables::set("KB_ESCAPE", new BigNumber(int(Keys::ESCAPE)));
    Variables::set("KB_UP", new BigNumber(int(Keys::UP)));
    Variables::set("KB_DOWN", new BigNumber(int(Keys::DOWN)));
    Variables::set("KB_LEFT", new BigNumber(int(Keys::LEFT)));
    Variables::set("KB_RIGHT", new BigNumber(int(Keys::RIGHT)));
    Variables::set("KB_SPACE", new BigNumber(int(Keys::SPACE)));
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
