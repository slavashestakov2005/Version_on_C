#ifndef LEXER_H_INCLUDED
#define LEXER_H_INCLUDED

#include <map>
#include <string>
#include <vector>
#include "token.h"
#include "../Exception/lexerexception.h"

class Lexer{
private:
    static std::map<std::string, TokenType> OPERATORS, KEYWORDS;
    static std::string OPERATOR_CHARS;
    int pos, length, row, col;
    std::string input;
    std::vector<Token*> tokens;
    void tokenizeNumber();
    void tokenizeHexNumber();
    void tokenizeOperator();
    void tokenizeWord();
    void tokenizeExtendedWord();
    void tokenizeText();
    void tokenizeComment();
    void tokenizeMultilineComment();
    void addToken(TokenType type);
    void addToken(TokenType type, std::string text);
    char peek(int position);
    char next();
    LexerException* error(std::string s);
public:
    Lexer(std::string input);
    std::vector<Token*> tokenize();
};

#endif // LEXER_H_INCLUDED
