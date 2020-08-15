#ifndef VALUES_H_INCLUDED
#define VALUES_H_INCLUDED

#include <string>
enum class Values{
    BOOL,
    NUMBER,
    STRING,
    ARRAY,
    MAP,
    NULL_,
    FUNCTION,
    CLASS,
};

std::string getValueName(Values value);

#endif // VALUES_H_INCLUDED
