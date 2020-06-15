#ifndef BREAKSTATEMENT_H_INCLUDED
#define BREAKSTATEMENT_H_INCLUDED

#include "statement.h"

class BreakStatement : public Statement{
public:
    Statements type(){ return Statements::BreakStatement; }
    void execute();
    operator std::string();
    void accept(Visitor* visitor);
    friend Visitor;
};

#endif // BREAKSTATEMENT_H_INCLUDED
