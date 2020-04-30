#ifndef CONTINUESTATEMENT_H_INCLUDED
#define CONTINUESTATEMENT_H_INCLUDED

#include "statement.h"
class ContinueStatement : public Statement{
public:
    Statements type(){ return Statements::ContinueStatement; }
    void execute();
    operator std::string();
    void accept(Visitor* visitor);
    friend Visitor;
};

#endif // CONTINUESTATEMENT_H_INCLUDED
