#include "classdeclaration.h"
#include "../Exception/unknownclassexception.h"

std::map<std::string, ClassDeclarationsStatement*> ClassDeclaration::declarations = { };

void ClassDeclaration::clear(){
    declarations.clear();
}

bool ClassDeclaration::isExists(std::string key){
    return declarations.find(key) != declarations.cend();
}

ClassDeclarationsStatement* ClassDeclaration::get(std::string key){
    if (!isExists(key)) throw new UnknownClassException(key);
    return declarations[key];
}

void ClassDeclaration::set(std::string key, ClassDeclarationsStatement* classDef){
    declarations[key] = new ClassDeclarationsStatement(*classDef);
}
