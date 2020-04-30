#include "mapexpression.h"
#include "../Lib/map.h"

Value* MapExpression::eval(){
    int siz = elements.size();
    Map* map = new Map(siz);
    for (auto now : elements){
        map -> set(now.first -> eval(), now.second -> eval());
    }
    return map;
}

MapExpression::operator std::string(){
    std::string result = "{";
    int siz = elements.size(), i = 0;
    for(auto now : elements){
        result += std::string(*(now.first -> eval()));
        result += ": ";
        result += std::string(*(now.second -> eval()));
        if (i < siz - 1) result += ", ";
        ++i;
    }
    result += "}";
    return result;
}

void MapExpression::accept(Visitor* visitor){
    visitor -> visit(this);
}
