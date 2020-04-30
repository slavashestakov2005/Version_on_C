#ifndef BLOCKSTATEMENT_H_INCLUDED
#define BLOCKSTATEMENT_H_INCLUDED

#include "statement.h"
#include <vector>
class BlockStatement : public Statement{
private:
    std::vector<Statement*> statements;
public:
    BlockStatement(){}
    Statements type(){ return Statements::BlockStatement; }
    void add(Statement* statement);
    void execute();
    operator std::string();
    ~BlockStatement();
    void accept(Visitor* visitor);
    friend Visitor;
};

#endif // BLOCKSTATEMENT_H_INCLUDED
