#include "objectcreationexpression.h"
#include "../Lib/classdeclaration.h"
#include "../Lib/classvalue.h"
#include "assignmentexpression.h"
#include "../Statement/functiondefinestatement.h"
#include <iostream>

Value* ObjectCreationExpression::eval(){
    std::cout << "ObjectCreation :: eval()\n";
    ClassDeclarationsStatement* ds = ClassDeclaration::get(name);
    ClassValue* instance = new ClassValue(name);
    for(AssignmentExpression* now : ds -> fields){
        std::cout << now -> variable  << std::endl;
        std::string fieldName = now -> variable;
        std::cout << fieldName << std::endl;
        instance -> addField(fieldName, now -> eval());
        std::cout << "Step :end\n";
    }
    for(FunctionDefineStatement* function : ds -> methods){
        instance -> addMethod(function -> name, new ClassMethod(function -> arguments, function -> body, instance));
    }
    int size = constructorArguments.size();
    std::vector<Value*> vec;
    for(int i = 0; i < size; ++i) vec.push_back(constructorArguments[i] -> eval());
    system("pause");
    instance -> callConstructor(vec);
    system("pause");
    return instance;
}

ObjectCreationExpression::operator std::string(){
    std::string result = "new " + name + "(";
    for(int i = 0; i < constructorArguments.size(); ++i){
        result += std::string(*(constructorArguments[i]));
        if (i < constructorArguments.size() - 1) result += ", ";
    }
    result += "]";
    return result;
}

ObjectCreationExpression::~ObjectCreationExpression(){
    std::cout << "delete ObjectCreation\n";
    for(int i = 0; i < constructorArguments.size(); ++i){
        delete constructorArguments[i];
        constructorArguments[i] = nullptr;
    }
}

void ObjectCreationExpression::accept(Visitor* visitor){
    visitor -> visit(this);
}
