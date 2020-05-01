#include "variableprinter.h"
#include "../Expression/assignmentexpression.h"
#include "../Expression/variableexpression.h"
#include <iostream>

void VariablePrinter::visit(AssignmentExpression* v){
    v -> expression -> accept(this);
    std::cout << v -> variable << std::endl;
}
void VariablePrinter::visit(VariableExpression* v){
    std::cout << v -> name << std::endl;
};
