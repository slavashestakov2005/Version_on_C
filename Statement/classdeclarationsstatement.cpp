#include "classdeclarationsstatement.h"
#include "../Lib/classdeclaration.h"
#include "../Expression/assignmentexpression.h"
#include "functiondefinestatement.h"

void ClassDeclarationsStatement::addField(AssignmentExpression* expr){
    fields.push_back(new AssignmentExpression(*expr));
}

void ClassDeclarationsStatement::addMethod(FunctionDefineStatement* statement){
    methods.push_back(new FunctionDefineStatement(*statement));
}

#include <iostream>
void ClassDeclarationsStatement::execute(){
    std::cout << "Class decl stat :: execute()";
    system("pause");
    ClassDeclaration::set(name, this);
    system("pause");
}

ClassDeclarationsStatement::operator std::string(){
    std::string result = "class " + name + "{\n ";
    int i = 0;
    for(AssignmentExpression* expr : fields){
        result += std::string(*expr);
        if (i < fields.size() - 1) result += ", ";
        ++i;
    }
    i = 0;
    for(FunctionDefineStatement* function : methods){
        result += std::string(*function);
        if (i < methods.size() - 1) result += ", ";
        ++i;
    }
    result += "}";
    return result;
}

ClassDeclarationsStatement::~ClassDeclarationsStatement(){
    std::cout << "Delete ClassDeclarationStatement\n";
    for(int i = 0; i < methods.size(); ++i){
        delete methods[i];
        methods[i] = nullptr;
    }
    for(int i = 0; i < fields.size(); ++i){
        delete fields[i];
        fields[i] = nullptr;
    }
}

void ClassDeclarationsStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}
