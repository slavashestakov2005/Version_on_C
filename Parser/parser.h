#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <vector>
#include "../Expression/expression.h"
#include "../Statement/statement.h"
#include "../Expression/functionalexpression.h"
#include "../Statement/foreacharraystatement.h"
#include "../Statement/foreachmapstatement.h"
#include "../Statement/functiondefinestatement.h"
#include "token.h"
#include "parseerrors.h"
#include "../Expression/containeracceselement.h"
/**
    @throw std::logic_error("Unknown expression")
    @throw std::logic_error(str)
    @throw std::logic_error("Unknown statement at 74")

**/
class Parser{
private:
    std::vector<Token*> tokens;
    int pos, size;
    ParseErrors parseErrors;
    int getErrorsLine();
    void recover();

    Statement* block();
    Statement* statementOrBlock();
    Statement* statement();
    Statement* assignmentStatement();
    Statement* ifelseStatement();
    Statement* whileStatement();
    Statement* doWhileStatement();
    Statement* forStatement();
    ForeachArrayStatement* foreachArrayStatement();
    ForeachMapStatement* foreachMapStatement();
    Statement* switchStatement();
    Statement* importStatement();
    Statement* tryStatement();
    FunctionDefineStatement* functionDefine();
    Expression* functionChain(Expression* nameExpression);
    FunctionalExpression* function(Expression* nameExpression);
    Expression* array();
    Expression* map();
    Statement* classDeclaration();
    Expression* expression();
    Expression* assignment();
    Expression* assignmentStrict();
    Expression* ternary();
    Expression* logicalOr();
    Expression* logicalAnd();
    Expression* bitOr();
    Expression* bitXor();
    Expression* bitAnd();
    Expression* equality();
    Expression* conditional();
    Expression* shift();
    Expression* additive();
    Expression* multiplicative();
    Expression* objectCreation();
    Expression* unary();
    Expression* exponential();
    Expression* primary();
    Expression* variable();
    Expression* value();

    Expression* qualifiedName();
    std::vector<ContainerAccessElement> variableSuffix();
    Token* get(int position);
    bool lookMatch(int position, TokenType type);
    bool match(TokenType type);
    Token* consume(TokenType type);
public:
    Parser(std::vector<Token*> tokens) : tokens(tokens), pos(0) { size = tokens.size(); }
    Statement* parse();
    ParseErrors getParseErrors();
};

#endif // PARSER_H_INCLUDED
