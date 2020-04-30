#include "importstatement.h"
#include "../Exception/unknownmoduleexception.h"
#include "../Modules/all.h"
#include "../path.h"
#include "../start.h"

void ImportStatement::execute(){
    if (!Path::getImpoted()) return;
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

ImportStatement::operator std::string(){
    return "import " + name;
}

ImportStatement::~ImportStatement(){}

void ImportStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}
