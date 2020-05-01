#include "functiondefinestatement.h"
#include "../Lib/functions.h"
#include "../Lib/userdefinedfunction.h"

void FunctionDefineStatement::execute(){
    Functions::set(name, new UserDefinedFunction(arguments, body));
}

void FunctionDefineStatement::execute(bool set){
    int start = arguments.getRequiredCounter();
    int finish = arguments.getArrayCounter() == 1 ? 100 : arguments.getSize();
    bool add = Functions::add(name, new UserDefinedFunction(arguments, body), start, finish);
    if (!add) throw std::logic_error("Cannot redefinition user's function \"" + name + "\"");
}

std::string FunctionDefineStatement::getName(){
    return name;
}

FunctionDefineStatement::operator std::string(){
    std::string result = name;
    result += " def (";
    for(unsigned i = 0; i < arguments.getSize(); ++i){
        result += std::string(arguments.get(i));
        if (i < arguments.getSize() - 1) result += ", ";
    }
    result += ") ";
    if(body -> type() == Statements::ReturnStatement) result += " = ";
    result += std::string(*body);
    return result;
}

FunctionDefineStatement::~FunctionDefineStatement(){
    delete body;
    body = nullptr;
}

void FunctionDefineStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}
