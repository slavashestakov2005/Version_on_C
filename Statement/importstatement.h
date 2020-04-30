#ifndef IMPORTSTATEMENT_H_INCLUDED
#define IMPORTSTATEMENT_H_INCLUDED

#include "statement.h"
#include "../Expression/expression.h"
#include "../Visitor/importadder.h"
class ImportStatement : public Statement{
private:
    std::string name;
public:
    ImportStatement(std::string name) : name(name) {}
    Statements type(){ return Statements::ImportStatement; }
    void execute();
    operator std::string();
    ~ImportStatement();
    void accept(Visitor* visitor);
    friend Visitor;
    friend ImportAdder;
};

#endif // IMPORTSTATEMENT_H_INCLUDED
