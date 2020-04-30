#include "userdefinedfunction.h"
#include "bignumber.h"
#include "../Statement/returnstatement.h"
#include "../Exception/argumentsmismatchexception.h"
#include "variables.h"
#include <sstream>
#include "../Lib/array.h"
#include <iostream>

int UserDefinedFunction::getArgsCount(){
    return arguments.getSize();
}

std::string UserDefinedFunction::getArgsName(int index){
    if (index < 0 || index >= getArgsCount()) return "";
    else return arguments.get(index).getName();
}

Value* UserDefinedFunction::execute(std::vector<Value*> values){
    std::cout << "Call me\t" << std::string(*body) << " with " << values.size() << "\n";
    std::cout << std::string(*Variables::get("this")) << "\n";
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
    std::cout << "Start excute\n";
    try{
        Variables::push();
        Variables::start();
        for(int i = 0; i < minimal; ++i){
            Variables::set(getArgsName(i), values[i]);
        }
        Array* array = new Array(siz - minimal);
        for(int i = minimal; i < siz; ++i){
            array -> set(i - minimal, values[i]);
        }
        /// add optional
        for(int i = minimal; i < total; ++i){
            Argument arg = arguments.get(i);
            if (arg.isArrayArgument()) Variables::set(arg.getName(), array);
            else Variables::set(arg.getName(), arg.getExpression() -> eval());
        }
        std::cout << "OK1\n";
        body -> execute();
        std::cout << "OK2\n";
    }
    catch(ReturnStatement* rs){
        Variables::pop();
        return rs -> getResult();
    }
    Variables::pop();
    return new BigNumber(0);
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