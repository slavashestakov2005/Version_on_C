#ifndef WHILESTATEMENT_H_INCLUDED
#define WHILESTATEMENT_H_INCLUDED

#include "statement.h"
#include "../Expression/expression.h"

class WhileStatement : public Statement{
private:
    Expression* condition;
    Statement* body;
public:
    WhileStatement(Expression* condition, Statement* body) : condition(condition), body(body) {}
    Statements type(){ return Statements::WhileStatement; }
    void execute();
    operator std::string();
    ~WhileStatement();
    void accept(Visitor* visitor);
    friend Visitor;
};

#endif // WHILESTATEMENT_H_INCLUDED
