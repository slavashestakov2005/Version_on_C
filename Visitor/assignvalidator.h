#ifndef ASSIGNVALIDATOR_H_INCLUDED
#define ASSIGNVALIDATOR_H_INCLUDED

#include "visitor.h"
/**
    @throw std::logic_error("Cannot assign value to constant")
**/
class AssignValidator : public Visitor{
    void visit(AssignmentExpression* v);
    void visit(ContainerAssignmentExpression* v);
};

#endif // ASSIGNVALIDATOR_H_INCLUDED
