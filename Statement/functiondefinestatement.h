#ifndef FUNCTIONDEFINESTATEMENT_H_INCLUDED
#define FUNCTIONDEFINESTATEMENT_H_INCLUDED

#include "statement.h"
#include <vector>
#include "../Visitor/functionadder.h"
#include "../Lib/arguments.h"
class FunctionDefineStatement : public Statement{
private:

public:
    Arguments arguments;
    Statement* body;
    std::string name;
    FunctionDefineStatement(std::string name, Arguments arguments, Statement* body)
    : name(name), arguments(arguments), body(body) {}
    Statements type(){ return Statements::FunctionDefineStatement; }
    void execute();
    std::string getName();
    operator std::string();
    ~FunctionDefineStatement();
    void accept(Visitor* visitor);
    friend Visitor;
    friend FunctionAdder;
};

#endif // FUNCTIONDEFINESTATEMENT_H_INCLUDED