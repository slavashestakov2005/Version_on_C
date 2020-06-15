#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

#include <string>
#include "tokentype.h"

class Token{
private:
    TokenType type;
    std::string text;
    int row, col;
public:
    Token(){}
    Token(TokenType type, std::string text, int row = 0, int col = 0) : type(type), text(text), row(row), col(col) {}
    int getRow();
    int getCol();
    std::string position();
    void setType(TokenType type);
    TokenType getType();
    void setText(std::string text);
    std::string getText();
    operator std::string();
};
std::ostream& operator<<(std::ostream& os, const Token& tok);
std::ostream& operator<<(std::ostream& os, Token* tok);

#endif // TOKEN_H_INCLUDED
