#include "breakstatement.h"
#include "continuestatement.h"
#include "forstatement.h"

void ForStatement::execute(){
    for(initialization -> execute(); termination -> eval() -> asBool(); increment -> execute()){
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

ForStatement::operator std::string(){
    return "for " + std::string(*initialization) + ", " + std::string(*termination) + ", " + std::string(*increment) + " " + std::string(*statement);
}

ForStatement::~ForStatement(){
    delete initialization;
    initialization = nullptr;
    delete termination;
    termination = nullptr;
    delete increment;
    increment = nullptr;
    delete statement;
    statement = nullptr;
}

void ForStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}
