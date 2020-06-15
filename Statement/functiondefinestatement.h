#ifndef FUNCTIONDEFINESTATEMENT_H_INCLUDED
#define FUNCTIONDEFINESTATEMENT_H_INCLUDED

#include <vector>
#include "statement.h"
#include "../Lib/arguments.h"
#include "../Visitor/functionadder.h"

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
    void execute(bool set);
    std::string getName();
    operator std::string();
    ~FunctionDefineStatement();
    void accept(Visitor* visitor);
    friend Visitor;
    friend FunctionAdder;
};

#endif // FUNCTIONDEFINESTATEMENT_H_INCLUDED
