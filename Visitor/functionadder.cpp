#include "functionadder.h"
#include "../Statement/functiondefinestatement.h"
#include "../Lib/functions.h"

void FunctionAdder::visit(FunctionDefineStatement* v){
    v -> body -> accept(this);
    if (Functions::isExists(v -> getName())){
        std::string str = "Cannot redefinition function \"" + v -> getName() + "\" from import";
        throw std::logic_error(str.c_str());
    }
    v -> execute();
}
