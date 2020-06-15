#include "functionalexpression.h"
#include "../Lib/functions.h"
#include "../Lib/userdefinedfunction.h"
#include "../Lib/variables.h"
#include "../Value/functionvalue.h"
#include "valueexpression.h"
#include "../Exception/variabledoesnotexistsexception.h"
#include "../Exception/unknownfunctionexception.h"
#include "../callstack.h"

void FunctionalExpression::addArguments(Expression* argument){
    arguments.push_back(argument);
}

Value* FunctionalExpression::eval(){
    std::vector<Value*> values;
    for(int i = 0; i < arguments.size(); ++i) values.push_back(arguments[i] -> eval());
    Function* f = consumeFunction(functionExpr);
    CallStack::push(std::string(*functionExpr), f);
    Value* result = f -> execute(values);
    CallStack::pop();
    return result;
}

Function* FunctionalExpression::consumeFunction(Expression* expr){
    try{
        Value* value = expr -> eval();
        if (value -> type() == Values::FUNCTION) return ((FunctionValue*)value) -> getFunction();
        return getFunction(value -> asString());
    }catch(VariableDoesNotExistsException* ex){
        return getFunction(ex -> getVariable());
    }
}

Function* FunctionalExpression::getFunction(std::string name){
    if (Functions::find(name, arguments.size())) return Functions::get(name, arguments.size());
    else if (Functions::isExists(name)) return Functions::get(name);
    else if (Variables::isExists(name)){
        if (Variables::get(name) -> type() == Values::FUNCTION) return ((FunctionValue*)Variables::get(name)) -> getFunction();
    }
    throw new UnknownFunctionException(name);
}

FunctionalExpression::operator std::string(){
    std::string result;
    if (functionExpr -> type() == Expressions::ValueExpression && ((ValueExpression*) functionExpr) -> value -> type() == Values::STRING){
        result += ((ValueExpression*) functionExpr) -> value -> asString() + "(";
    }
    else result += std::string(*functionExpr) + "(";
    for(int i = 0; i < arguments.size(); ++i){
        result += std::string(*arguments[i]);
        if (i < arguments.size() - 1) result += ", ";
    }
    result += ")";
    return result;
}

FunctionalExpression::~FunctionalExpression(){
    for(unsigned i = 0; i < arguments.size(); ++i){
        delete arguments[i];
        arguments[i] = nullptr;
    }
}

void FunctionalExpression::accept(Visitor* visitor){
    visitor -> visit(this);
}
