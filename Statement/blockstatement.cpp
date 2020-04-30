#include "blockstatement.h"

void BlockStatement::add(Statement* statement){
    statements.push_back(statement);
}

#include <iostream>
void BlockStatement::execute(){
    for(int i = 0; i < statements.size(); ++i){
        std::cout << "Block :: execute()\n";
        statements[i] -> execute();
    }
}

BlockStatement::operator std::string(){
    std::string result = "{";
    for(int i = 0; i < statements.size(); ++i){
        result += std::string(*statements[i]);
        result += "\n";
    }
    result += "}";
    return result;
}

BlockStatement::~BlockStatement(){
    for(int i = 0; i < statements.size(); ++i) {
        delete statements[i];
        statements[i] = nullptr;
    }
}

void BlockStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}
