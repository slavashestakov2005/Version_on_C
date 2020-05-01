#include "importadder.h"
#include "../Statement/importstatement.h"

void ImportAdder::visit(ImportStatement* v){
    v -> execute();
}
