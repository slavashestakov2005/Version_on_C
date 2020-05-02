#ifndef STD_H_INCLUDED
#define STD_H_INCLUDED

#include "module.h"

/**
    @throw std::logic_error("Fewer arguments expected")
    @throw std::logic_error("One argument expected")
**/

class Std : public Module<Std> {
public:
    static void initConstants(){}
    static void initFunctions();
};

#endif // STD_H_INCLUDED
