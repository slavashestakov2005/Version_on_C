#include "assignvalidator.h"
#include "../Expression/assignmentexpression.h"
#include "../Lib/variables.h"
#include <stdexcept>
void AssignValidator::visit(AssignmentExpression* v){
    v -> expression -> accept(this);
    if (Variables::isExists(v -> variable)) throw std::logic_error("Cannot assign value to constant");
}
