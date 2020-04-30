class FunctionDefineStatement;

#ifndef FUNCTIONADDER_H_INCLUDED
#define FUNCTIONADDER_H_INCLUDED

#include "visitor.h"
class FunctionAdder : public Visitor{
public:
    void visit(FunctionDefineStatement* v);
};

#endif // FUNCTIONADDER_H_INCLUDED
