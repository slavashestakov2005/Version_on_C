#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include "module.h"

class Global : public Module<Global> {
public:
    static void initConstants();
    static void initFunctions();
};

#endif // GLOBAL_H_INCLUDED
