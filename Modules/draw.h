#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

#include "module.h"

/**
    @throw std::logic_error("One or two or three arguments expected")
    @throw std::logic_error("Four arguments expected")
    @throw std::logic_error("Three arguments expected")
    @throw std::logic_error("Zero arguments expected");
**/

class Draw : public Module<Draw> {
public:
    static void initConstants();
    static void initFunctions();
};

#endif // DRAW_H_INCLUDED
