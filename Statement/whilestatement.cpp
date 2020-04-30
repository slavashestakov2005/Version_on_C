#include "whilestatement.h"
#include "breakstatement.h"
#include "continuestatement.h"

void WhileStatement::execute(){
    while((condition -> eval()) -> getDouble()){
        try{
            statement -> execute();
        }
        catch(BreakStatement* bs){
            break;
        }
        catch(ContinueStatement* cs){
            //continue;
        }
    }
}

WhileStatement::operator std::string(){
    return "while " + std::string(*condition) + " " + std::string(*statement);
}

WhileStatement::~WhileStatement(){
    delete condition;
    condition = nullptr;
    delete statement;
    statement = nullptr;
}

void WhileStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}
