#ifndef FILES_H_INCLUDED
#define FILES_H_INCLUDED

#include "module.h"

class Files : public Module<Files> {
public:
    static void initConstants(){}
    static void initFunctions();
};

#endif // FILES_H_INCLUDED
