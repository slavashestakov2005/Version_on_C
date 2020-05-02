#ifndef FUNCTIONAL_H_INCLUDED
#define FUNCTIONAL_H_INCLUDED

#include "module.h"

class Functional : public Module<Functional> {
public:
    static void initConstants(){}
    static void initFunctions();
};

#endif // FUNCTIONAL_H_INCLUDED
