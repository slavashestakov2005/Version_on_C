#ifndef MATH_H_INCLUDED
#define MATH_H_INCLUDED

#include "module.h"

/**
    @throw std::logic_error("One argument expected")
    @throw std::logic_error("Two argument expected")
**/

class Math : public Module<Math> {
public:
    static void initConstants();
    static void initFunctions();
};

#endif // MATH_H_INCLUDED
