#include "switchstatement.h"
#include "breakstatement.h"
#include "continuestatement.h"

namespace{
    bool equals(Value* val1, Value* val2){
        if (val1 -> type != val2 -> type) return false;
        if (val1 -> type == Values::ARRAY) return val1 -> getString() == val2 -> getString();
        if (val1 -> type == Values::NUMBER) return val1 -> getBignum() == val2 -> getBignum();
        if (val1 -> type == Values::STRING) return val1 -> getString() == val2 -> getString();
        return false;
    }
}

void SwitchStatement::execute(){
    bool trueCase = false;
    Value* val = start -> eval();
    try{
        for(unsigned i = 0; i < body.size(); ++i){
            if (equals(val, body[i].first -> eval())){
                trueCase = true;
                try{
                    body[i].second -> execute();
                } catch(ContinueStatement* cs){
                    // continue;
                }
            }
        }
        if (!trueCase && defaultCase != nullptr) defaultCase -> execute();
    } catch(BreakStatement* bs){
        // break;
    }
}

SwitchStatement::operator std::string(){
    std::string result = "switch " + std::string(*start) + " {\n";
    for (unsigned i = 0; i < body.size(); ++i){
        result += "case ";
        result += std::string(*body[i].first);
        result += " : ";
        result += std::string(*body[i].second);
        result += "\n";
    }
    if (defaultCase != nullptr){
        result += "default : ";
        result += std::string(*defaultCase);
        result += "\n";
    }
    result += "}\n";
    return result;
}

SwitchStatement::~SwitchStatement(){
    delete start;
    start = nullptr;
    for(unsigned i = 0; i < body.size(); ++i){
        delete body[i].first;
        body[i].first = nullptr;
        delete body[i].second;
        body[i].second = nullptr;
    }
    delete defaultCase;
    defaultCase = nullptr;
}

void SwitchStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}
