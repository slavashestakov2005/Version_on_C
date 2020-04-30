#include "valueexpression.h"

ValueExpression::ValueExpression(Value* val){
    if (val -> type == Values::ARRAY) value = val;
    else if (val -> type == Values::STRING) value = new String(*(String*)val);
    else if (val -> type == Values::BOOL) value = new Bool(*(Bool*)val);
    else if (val -> type == Values::FUNCTION) value = new FunctionValue(*(FunctionValue*)val);
    else if (val -> type == Values::MAP) value = new Map(*(Map*)val);
    else if (val -> type == Values::NUMBER) value = new BigNumber(*(BigNumber*)val);
    else if (val -> type == Values::NULL_) value = new Null();
}

Value* ValueExpression::eval(){
    return value;
}

ValueExpression::operator std::string(){
    return std::string(*value);
}

ValueExpression::~ValueExpression(){
    delete value;
    value = nullptr;
}

void ValueExpression::accept(Visitor* visitor){
    visitor -> visit(this);
}
