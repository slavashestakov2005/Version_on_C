#include "importstatement.h"
#include "../Exception/unknownmoduleexception.h"
#include "../Modules/all.h"
#include "../path.h"
#include "../start.h"
#include "../Lib/functions.h"
#include "../Lib/variables.h"
#include "../Lib/map.h"
#include "../Lib/string.h"

void ImportStatement::execute(){
    if (!Path::getImpoted()) return;
    bool named = moduleName != "";
    if (named){
        Variables::setInsert(false);
        Functions::setInsert(false);
    }
    for(std::string name : names){
        if (name == "std") Std::init();
        else if (name == "math") Math::init();
        else if (name == "draw") Draw::init();
        else if (name == "types") Types::init();
        else if (name == "functional") Functional::init();
        else if (name == "chemistry") Chemistry::init();
        else if (name == "files") Files::init();
        else{
            try{
                if (name.find("\\") == std::string::npos && name.find("/") == std::string::npos) name = Path::getPath() + name;
                Start start(name);
                start.start();
            }catch(...){
                throw new UnknownModuleException(name);
            }
        }
    }
    if (named){
        std::map<std::string, Value*> variables = Variables::getNow();
        std::map<std::string, Function*> functions = Functions::getNow();
        Map* map = new Map(1);
        for(auto x : variables) map -> set(new String(x.first), x.second);
        for(auto x : functions) map -> set(new String(x.first), x.second);
        map -> setThisMap(true);
        Variables::setInsert(true);
        Functions::setInsert(true);
        Variables::set(moduleName, map);
    }
    Variables::setInsert(true);
    Functions::setInsert(true);
}

ImportStatement::operator std::string(){
    std::string result = "import [";
    for(int i = 0; i < names.size(); ++i){
        result += names[i];
        if (i < names.size() - 1) result += ", ";
    }
    result += (moduleName == "" ? "" : " as " + moduleName);
    return result;
}

ImportStatement::~ImportStatement(){}

void ImportStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}
