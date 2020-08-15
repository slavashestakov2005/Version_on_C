// [[not imported module]]
#include "files.h"
#include "../Lib/functions.h"
#include "../Lib/variables.h"
#include "../Value/numbervalue.h"
#include "../Value/stringvalue.h"
#include "../Exception/argumentsmismatchexception.h"
#include <fstream>
#include <iostream>

namespace{
    std::fstream file;
    bool bad = true;

    class Fopen : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One arguments expected");
            file.open(values[0] -> asString());
            if (!file){
                bad = false;
                return new NumberValue(-1);
            }
            bad = false;
            return new NumberValue(0);
        }
    };

    class Fclose : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 0) throw new ArgumentsMismatchException("Zero arguments expected");
            file.close();
        }
    };

    class ReadLine : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 0) throw new ArgumentsMismatchException("Zero arguments expected");
            std::string line;
            if (file) std::getline(file, line);
            return new StringValue(line);
        }
    };

    class WriteLine : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One arguments expected");
            if (file && file.tellg() < file.end) file << values[0] -> asString();
            else if (!bad){
                std::cout << "Here\n";
                file.seekg(0, file.beg);
                file << values[0] -> asString();
            }
            else return new NumberValue(-1);
            return new NumberValue(0);
        }
    };
}

void Files::initFunctions(){
    Functions::set("fopen", new Fopen());
    Functions::set("fclose", new Fclose());
    Functions::set("readline", new ReadLine());
    Functions::set("writeline", new WriteLine());
}
