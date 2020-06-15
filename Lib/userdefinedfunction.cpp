#include <sstream>
#include "variables.h"
#include "userdefinedfunction.h"
#include "../Exception/argumentsmismatchexception.h"
#include "../Statement/returnstatement.h"
#include "../Value/arrayvalue.h"
#include "../Value/nullvalue.h"

int UserDefinedFunction::getArgsCount(){
    return arguments.getSize();
}

std::string UserDefinedFunction::getArgsName(int index){
    if (index < 0 || index >= getArgsCount()) return "";
    else return arguments.get(index).getName();
}

Value* UserDefinedFunction::execute(std::vector<Value*> values){
    int siz = values.size();
    int requiredArgsCount = arguments.getRequiredCounter();
    int total = getArgsCount();
    int positionArguments = total - arguments.getArrayCounter();
    int minimal = std::min(positionArguments, siz);
    if (siz < requiredArgsCount){
        std::string result = "Arguments count mismatch. ";
        std::ostringstream is;
        is << siz << " < " << requiredArgsCount;
        result += is.str();
        throw new ArgumentsMismatchException(result);
    }
    if (siz > total && arguments.getArrayCounter() == 0){
        std::string result = "Arguments count mismatch. ";
        std::ostringstream is;
        is << siz << " > " << total;
        result += is.str();
        throw new ArgumentsMismatchException(result);
    }
    try{
        Variables::push();
        for(int i = 0; i < minimal; ++i){
            Variables::set(getArgsName(i), values[i]);
        }
        ArrayValue* array = new ArrayValue(siz - minimal);
        for(int i = minimal; i < siz; ++i){
            array -> set(i - minimal, values[i]);
        }
        /// add optional
        for(int i = minimal; i < total; ++i){
            Argument arg = arguments.get(i);
            if (arg.isArrayArgument()) Variables::set(arg.getName(), array);
            else Variables::set(arg.getName(), arg.getExpression() -> eval());
        }
        body -> execute();
    }
    catch(ReturnStatement* rs){
        Variables::pop();
        return rs -> getResult();
    }
    Variables::pop();
    return NullValue::NULL_;
}

UserDefinedFunction::operator std::string(){
    std::string result = "def (";
    for(int i = 0; i < arguments.getSize(); ++i){
        result += std::string(arguments.get(i));
        if (i < arguments.getSize() - 1) result += ", ";
    }
    result += ") ";
    if(body -> type() == Statements::ReturnStatement) result += "= ";
    result += std::string(*body);
    return result;
}
