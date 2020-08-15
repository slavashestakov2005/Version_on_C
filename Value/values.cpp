#include "values.h"

namespace {
    std::string mas[] = {
        "Bool", "Number", "String", "Array", "Map", "Null", "Function", "Class"
    };
}

std::string getValueName(Values value){
    return mas[(int) value];
}
