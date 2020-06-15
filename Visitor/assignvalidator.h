#ifndef ASSIGNVALIDATOR_H_INCLUDED
#define ASSIGNVALIDATOR_H_INCLUDED

#include "visitor.h"

class AssignValidator : public Visitor{
    void visit(AssignmentExpression* v);
    void visit(ContainerAssignmentExpression* v);
};

#endif // ASSIGNVALIDATOR_H_INCLUDED
