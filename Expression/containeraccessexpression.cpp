#include "containeraccessexpression.h"
#include "../Lib/variables.h"
#include "../Lib/bignumber.h"
#include "../Lib/string.h"
#include "../Lib/classvalue.h"
#include "../Exception/typeexception.h"
#include "variableexpression.h"

ContainerAccessExpression::ContainerAccessExpression(std::string variable, std::vector<ContainerAccessElement> indices){
    (*this) = ContainerAccessExpression(new VariableExpression(variable), indices);
}

ContainerAccessExpression::ContainerAccessExpression(Expression* root, std::vector<ContainerAccessElement> indices) : root(root), indices(indices) {
    rootVariable = root -> type() == Expressions::VariableExpression;
}

Value* ContainerAccessExpression::eval(){
    return get();
}

Value* ContainerAccessExpression::get(){
    Value* container = getContainer();
    Value* lastindex = lastIndex();
    bool lastdot = lastDot();
    switch(container -> type){
        case (Values::ARRAY):
            if (lastdot) throw new std::logic_error("Cannot used DOT for array");
            return ((Array*) container) -> access(lastindex);
        case Values::MAP:
            if (lastdot && !((Map*) container) -> isThisMap()) throw new std::logic_error("Cannot used DOT for map");
            return ((Map*) container) -> get(lastindex);
        case Values::STRING:
            if (lastdot) throw new std::logic_error("Cannot used DOT for string");
            return ((String*) container) -> access(lastindex);
        case Values::CLASS:
            if (!lastdot) throw new std::logic_error("Cannot used [] for class");
            return ((ClassValue*) container) -> access(lastindex);
        default:
            throw new TypeException("Array, map, string or class expected");
    }
}

Value* ContainerAccessExpression::set(Value* value){
    Value* container = getContainer();
    Value* lastindex = lastIndex();
    bool lastdot = lastDot();
    switch(container -> type){
        case (Values::ARRAY) : {
            if (lastdot) throw new std::logic_error("Cannot used DOT for array");
            int arrayIndex = (int) lastindex -> getDouble();
            ((Array*) container) -> set(arrayIndex, value);
            break;
        }
        case (Values::MAP) :
            if (lastdot && !((Map*) container) -> isThisMap()) throw new std::logic_error("Cannot used DOT for map");
            ((Map*) container) -> set(lastindex, value);
            break;
        case Values::CLASS :
            if (!lastdot) throw new std::logic_error("Cannot used [] for class");
            ((ClassValue*) container) -> set(lastindex, value);
            break;
        default:
            throw new TypeException("Array, map or class expected");
    }
    return value;
}

Value* ContainerAccessExpression::getCopyElement(){
    Value* container = getContainer();
    switch(container -> type){
        case Values::ARRAY : return new Array(((Array*) container) -> getCopyElement());
        case Values::MAP : return ((Map*) container) -> getCopyElement();
        default: return container;
    }
}

Value* ContainerAccessExpression::getContainer(){
    Value* container = root -> eval();
    int last = indices.size() - 1;
    for(int i = 0; i < last; ++i){
        Value* ind = index(i);
        bool isdot = isDot(i);
        switch(container -> type){
            case (Values::ARRAY): {
                if (isdot) throw new std::logic_error("Cannot used DOT for array");
                int arrayIndex = (int) ind -> getDouble();
                container = ((Array*) container) -> get(arrayIndex);
                break;
            }
            case Values::MAP: {
                if (isdot && !((Map*) container) -> isThisMap()) throw new std::logic_error("Cannot used DOT for map");
                container = ((Map*) container) -> get(ind);
                break;
            }
            case Values::CLASS: {
                if (!isdot) throw new std::logic_error("Cannot used [] for class");
                container = ((ClassValue*) container) -> get(ind);
                break;
            }
            default:
                throw new TypeException("Array or map expected");
        }
    }
    return container;
}

Value* ContainerAccessExpression::lastIndex(){
    return index(indices.size() - 1);
}

bool ContainerAccessExpression::lastDot(){
    return isDot(indices.size() - 1);
}

Value* ContainerAccessExpression::index(int index){
    return indices[index].eval();
}

bool ContainerAccessExpression::isDot(int index){
    return indices[index].isDot();
}

ContainerAccessExpression::operator std::string(){
    std::string result = std::string(*root);
    for(unsigned i = 0; i < indices.size() - 1; ++i){
        result += std::string(indices[i]);
    }
    return result;
}

void ContainerAccessExpression::accept(Visitor* visitor){
    visitor -> visit(this);
}
