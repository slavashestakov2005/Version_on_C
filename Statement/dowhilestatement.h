#ifndef DOWHILESTATEMENT_H_INCLUDED
#define DOWHILESTATEMENT_H_INCLUDED

#include "statement.h"
#include "../Expression/expression.h"

class DoWhileStatement : public Statement{
private:
    Expression* condition;
    Statement* body;
public:
    DoWhileStatement(Expression* condition, Statement* body) : condition(condition), body(body) {}
    Statements type(){ return Statements::DoWhileStatement; }
    void execute();
    operator std::string();
    ~DoWhileStatement();
    void accept(Visitor* visitor);
    friend Visitor;
};

#endif // DOWHILESTATEMENT_H_INCLUDED
