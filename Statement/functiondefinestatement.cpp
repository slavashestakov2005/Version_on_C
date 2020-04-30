#include "functiondefinestatement.h"
#include "../Lib/functions.h"
#include "../Lib/userdefinedfunction.h"

void FunctionDefineStatement::execute(){
    Functions::set(name, new UserDefinedFunction(arguments, body));
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
