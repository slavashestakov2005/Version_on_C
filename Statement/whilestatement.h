#ifndef WHILESTATEMENT_H_INCLUDED
#define WHILESTATEMENT_H_INCLUDED

#include "statement.h"
#include "../Expression/expression.h"
class WhileStatement : public Statement{
private:
    Expression* condition;
    Statement* statement;
public:
    WhileStatement(Expression* condition, Statement* statement) : condition(condition), statement(statement) {}
    Statements type(){ return Statements::WhileStatement; }
    void execute();
    operator std::string();
    ~WhileStatement();
    void accept(Visitor* visitor);
    friend Visitor;
};

#endif // WHILESTATEMENT_H_INCLUDED
