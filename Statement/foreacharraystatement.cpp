#include "breakstatement.h"
#include "continuestatement.h"
#include "foreacharraystatement.h"
#include "../Lib/variables.h"
#include "../Value/arrayvalue.h"

void ForeachArrayStatement::execute(){
    Value* start = Variables::isExists(variable) ? Variables::get(variable) : nullptr;
    int siz = ((ArrayValue*)(container -> eval())) -> getSize();
    for (int i = 0; i < siz; ++i){
        Variables::set(variable, ((ArrayValue*)(container -> eval())) -> get(i));
        try{
            body -> execute();
        }
        catch(BreakStatement* bs){
            break;
        }
        catch(ContinueStatement* cs){
            //continue;
        }
    }
    if (start != nullptr){
        Variables::set(variable, start);
    }
}

ForeachArrayStatement::operator std::string(){
    return "for " + variable + " : " + std::string(*container) + " " + std::string(*body);
}

ForeachArrayStatement::~ForeachArrayStatement(){
    delete container;
    delete body;
}

void ForeachArrayStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}
