#include "continuestatement.h"

void ContinueStatement::execute(){
    throw this;
}

ContinueStatement::operator std::string(){
    return "continue";
}

void ContinueStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}
