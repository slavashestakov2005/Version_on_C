#include "containeracceselement.h"
#include "../Lib/value.h"

Value* ContainerAccessElement::eval(){
    return expression -> eval();
}

bool ContainerAccessElement::isDot() {
    return dot;
}

ContainerAccessElement::operator std::string(){
    if (dot) return "." + std::string(*expression);
    else return "[" + std::string(*expression) + "]";
}
