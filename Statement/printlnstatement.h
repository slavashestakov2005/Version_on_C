#ifndef PRINTLNSTATEMENT_H_INCLUDED
#define PRINTLNSTATEMENT_H_INCLUDED

#include "statement.h"
#include "../Expression/expression.h"

class PrintlnStatement : public Statement{
private:
    Expression* expression;
public:
    PrintlnStatement(Expression* expression) : expression(expression) {}
    Statements type(){ return Statements::PrintlnStatement; }
    void execute();
    operator std::string();
    ~PrintlnStatement();
    void accept(Visitor* visitor);
    friend Visitor;
};

#endif // PRINTLNSTATEMENT_H_INCLUDED
