#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include "module.h"

class Types : public Module<Types> {
public:
    static void initConstants();
    static void initFunctions();
};

#endif // TYPES_H_INCLUDED
