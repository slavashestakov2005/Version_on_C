#include "dowhilestatement.h"
#include "breakstatement.h"
#include "continuestatement.h"

void DoWhileStatement::execute(){
    do{
        try{
            statement -> execute();
        }
        catch(BreakStatement* bs){
            break;
        }
        catch(ContinueStatement* cs){
            //continue;
        }
    }while((condition -> eval()) -> getDouble());
}

DoWhileStatement::operator std::string(){
    return "do " + std::string(*statement) + " while " + std::string(*condition);
}

DoWhileStatement::~DoWhileStatement(){
    delete statement;
    statement = nullptr;
    delete condition;
    condition = nullptr;
}

void DoWhileStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}
