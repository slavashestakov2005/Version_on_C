#include "classmethod.h"
#include "variables.h"
#include "classvalue.h"

ClassMethod::ClassMethod(Arguments args, Statement* body, ClassValue* classInstance)
    : UserDefinedFunction(args, body), classInstance(classInstance) { }

Value* ClassMethod::execute(std::vector<Value*> values){
    Variables::push();
    Variables::set("this", classInstance -> getThisMap());
    try{
        UserDefinedFunction::execute(values);
    } catch(std::exception* ex){
        Variables::pop();
        throw ex;
    } catch(std::exception& ex){
        Variables::pop();
        throw ex;
    }
    Variables::pop();
}
