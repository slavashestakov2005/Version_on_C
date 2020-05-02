#ifndef CHEMISTRY_H_INCLUDED
#define CHEMISTRY_H_INCLUDED

#include "module.h"

class Chemistry : public Module<Chemistry> {
public:
    static void initConstants(){}
    static void initFunctions();
};

#endif // CHEMISTRY_H_INCLUDED
