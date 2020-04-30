#ifndef CLASSDECLARATIONSSTATEMENT_H_INCLUDED
#define CLASSDECLARATIONSSTATEMENT_H_INCLUDED

#include "statement.h"
#include <vector>

class ClassDeclarationsStatement : public Statement{
private:
    std::string name;
public:
    std::vector<FunctionDefineStatement*> methods;
    std::vector<AssignmentExpression*> fields;
    ClassDeclarationsStatement() : name("") { }
    ClassDeclarationsStatement(std::string name) : name(name) { }
    Statements type(){ return Statements::ClassDeclarationsStatement; }
    void addField(AssignmentExpression* expr);
    void addMethod(FunctionDefineStatement* statement);
    void execute();
    operator std::string();
    ~ClassDeclarationsStatement();
    void accept(Visitor* visitor);
    friend Visitor;
};

#endif // CLASSDECLARATIONSSTATEMENT_H_INCLUDED
