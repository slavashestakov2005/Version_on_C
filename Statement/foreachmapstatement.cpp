#include "foreachmapstatement.h"
#include "../Lib/variables.h"
#include "../Lib/map.h"
#include "breakstatement.h"
#include "continuestatement.h"

void ForeachMapStatement::execute(){
    Value* startKey = Variables::isExists(key) ? Variables::get(key) : nullptr;
    Value* startValue = Variables::isExists(value) ? Variables::get(value) : nullptr;

    Map* map = static_cast<Map*>(container -> eval());
    int siz = map -> getSize();
    std::map<Value*, Value*>::iterator iter = map -> iter();
    int i = 0;
    while(i < siz){
        Variables::set(key, iter -> first);
        Variables::set(value, iter -> second);
        try{
            body -> execute();
        }
        catch(BreakStatement* bs){
            break;
        }
        catch(ContinueStatement* cs){
            //continue;
        }
        ++iter;
        ++i;
    }
    if (startKey != nullptr){
        Variables::set(key, startKey);
    }
    if (startValue != nullptr){
        Variables::set(value, startValue);
    }
}

ForeachMapStatement::operator std::string(){
    return "for " + key + ", " + value + " : " + std::string(*container) + " " + std::string(*body);
}

ForeachMapStatement::~ForeachMapStatement(){
    delete container;
    delete body;
}

void ForeachMapStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}
