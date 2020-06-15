#ifndef FORSTATEMENT_H_INCLUDED
#define FORSTATEMENT_H_INCLUDED

#include "statement.h"
#include "../Expression/expression.h"

class ForStatement: public Statement{
private:
    Statement* initialization;
    Expression* termination;
    Statement* increment;
    Statement* statement;
public:
    ForStatement(Statement* initialization, Expression* termination, Statement* increment, Statement* statement)
    : initialization(initialization), termination(termination), increment(increment), statement(statement) {}
    Statements type(){ return Statements::ForStatement; }
    void execute();
    operator std::string();
    ~ForStatement();
    void accept(Visitor* visitor);
    friend Visitor;
};

#endif // FORSTATEMENT_H_INCLUDED
