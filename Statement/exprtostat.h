#ifndef EXPRTOSTAT_H_INCLUDED
#define EXPRTOSTAT_H_INCLUDED

#include "statement.h"
#include "../Expression/expression.h"

class ExprToStat : public Statement{
    Expression* expression;
public:
    ExprToStat(Expression* expression) : expression(expression) {}
    Statements type(){ return Statements::ExprToStat; }
    void execute();
    operator std::string();
    ~ExprToStat();
    void accept(Visitor* visitor);
    friend Visitor;
};

#endif // EXPRTOSTAT_H_INCLUDED
