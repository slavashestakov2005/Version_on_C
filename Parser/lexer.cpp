#include "lexer.h"
#include <stdexcept>
std::map<std::string, TokenType> Lexer::OPERATORS = {
    std::make_pair("+", TokenType::PLUS),
    std::make_pair("-", TokenType::MINUS),
    std::make_pair("*", TokenType::STAR),
    std::make_pair("/", TokenType::SLASH),
    std::make_pair("%", TokenType::PERCENT),

    std::make_pair("+=", TokenType::PLUSEQ),
    std::make_pair("-=", TokenType::MINUSEQ),
    std::make_pair("*=", TokenType::STAREQ),
    std::make_pair("/=", TokenType::SLASHEQ),
    std::make_pair("%=", TokenType::PERCENTEQ),

    std::make_pair("<<", TokenType::LTLT),
    std::make_pair(">>", TokenType::GTGT),

    std::make_pair("<<=", TokenType::LTLTEQ),
    std::make_pair(">>=", TokenType::GTGTEQ),

    std::make_pair("++", TokenType::PLUSPLUS),
    std::make_pair("--", TokenType::MINUSMINUS),

    std::make_pair("=", TokenType::EQ),
    std::make_pair("<", TokenType::LT),
    std::make_pair(">", TokenType::GT),
    std::make_pair("==", TokenType::EQEQ),
    std::make_pair("!=", TokenType::EXCLEQ),
    std::make_pair("<=", TokenType::LTEQ),
    std::make_pair(">=", TokenType::GTEQ),

    std::make_pair("!", TokenType::EXCL),
    std::make_pair("|", TokenType::BAR),
    std::make_pair("||", TokenType::BARBAR),
    std::make_pair("&", TokenType::AMP),
    std::make_pair("&&", TokenType::AMPAMP),
    std::make_pair("^", TokenType::CARET),
    std::make_pair("~", TokenType::TILDE),

    std::make_pair("|=", TokenType::BAREQ),
    std::make_pair("&=", TokenType::AMPEQ),
    std::make_pair("^=", TokenType::CARETEQ),

    std::make_pair("(", TokenType::LPAREN),
    std::make_pair(")", TokenType::RPAREN),
    std::make_pair("{", TokenType::LBRACE),
    std::make_pair("}", TokenType::RBRACE),
    std::make_pair("[", TokenType::LBRACKET),
    std::make_pair("]", TokenType::RBRACKET),
    std::make_pair(",", TokenType::COMMA),
    std::make_pair(".", TokenType::DOT),

    std::make_pair("?", TokenType::QUESTION),
    std::make_pair(":", TokenType::COLON),
    std::make_pair("::", TokenType::COLONCOLON),
};
std::string Lexer::OPERATOR_CHARS = "+-*/%(){}[]=<>!&|.,?:^~";

Lexer::Lexer(std::string input){
    this -> input = input;
    length = input.size();
    pos = 0;
    col = 1;
    row = 1;
}

std::vector<Token*> Lexer::tokenize(){
    while(pos < length){
        char current = peek(0);
        if (isdigit(current)) tokenizeNumber();
        else if (islower(current) || isupper(current) || current == '_' || current == '$'/* || current >= 'а' && current <= 'я' || current >= 'А' && current <= 'Я'*/) tokenizeWord();
        else if (current == '#'){
            next();
            tokenizeHexNumber();
        }
        else if (current == '"') tokenizeText();
        else if (current == '\'') tokenizeExtendedWord();
        else if (Lexer::OPERATOR_CHARS.find(current) != -1){
            tokenizeOperator();
        }
        else next();
    }
    return tokens;
}

void Lexer::tokenizeNumber(){
    std::string str;
    char current = peek(0);
    while(true){
        if (current == '.'){
            if (str.find(current) != -1) error("Invalid float number");
        } else if(!isdigit(current)) break;
        str += current;
        current = next();
    }
    addToken(TokenType::NUMBER, str);
}

void Lexer::tokenizeHexNumber(){
    std::string str;
    char current = peek(0);
    while(isdigit(current) || current >= 'A' && current <= 'F' || current >= 'a' && current <= 'f'){
        str += current;
        current = next();
    }
    addToken(TokenType::HEX_NUMBER, str);
}

void Lexer::tokenizeText(){
    next(); ///skip "
    std::string str;
    char current = peek(0);
    while(true){
        if (current == '\0') throw error("Reached end of file while parsing text string");
        if (current == '\\'){
            current = next();
            switch(current){
                case '"' : str += '"'; current = next(); continue;
                case '0' : str += '\0'; current = next(); continue;
                case 'r' : str += '\r'; current = next(); continue;
                case 'v' : str += '\v'; current = next(); continue;
                case 'a' : str += '\a'; current = next(); continue;
                case 'n' : str += '\n'; current = next(); continue;
                case 't' : str += '\t'; current = next(); continue;
            }
            str += '\\';
            continue;
        }
        if (current == '"') break;
        str += current;
        current = next();
    }
    next(); /// skip "
    addToken(TokenType::TEXT, str);
}

void Lexer::tokenizeExtendedWord(){
    next(); ///skip '
    std::string str;
    char current = peek(0);
    while(true){
        if (current == '\0') throw error("Reached end of file while parsing extended word");
        if (current == '\n' || current == '\r') throw error("Reached end of line while parsing extended word");
        if (current == '\'') break;
        str += current;
        current = next();
    }
    next(); /// skip '
    addToken(TokenType::WORD, str);
}

void Lexer::tokenizeOperator(){
    char current = peek(0);
    if (current == '/'){
        if (peek(1) == '/'){
            next();
            next();
            tokenizeComment();
            return;
        }
        else if(peek(1) == '*'){
            next();
            next();
            tokenizeMultilineComment();
            return;
        }
    }
    std::string str;
    while(true){
        std::string text = str;
        if (OPERATORS.find(text + current) == OPERATORS.cend() && text != ""){
            addToken(OPERATORS[text]);
            return;
        }
        str += current;
        current = next();
    }
}

void Lexer::tokenizeWord(){
    std::string str;
    char current = peek(0);
    while(true){
        if(!isdigit(current) && !islower(current) && !isupper(current) && current != '_' && current != '$' && !(current >= 'А' && current <= 'Я') && !(current >= 'а' && current <= 'я')) break;
        str += current;
        current = next();
    }
    if (str == "print") addToken(TokenType::PRINT);
    else if (str == "println") addToken(TokenType::PRINTLN);
    else if (str == "if") addToken(TokenType::IF);
    else if (str == "elif") addToken(TokenType::ELIF);
    else if (str == "else") addToken(TokenType::ELSE);
    else if (str == "while") addToken(TokenType::WHILE);
    else if (str == "for") addToken(TokenType::FOR);
    else if (str == "do") addToken(TokenType::DO);
    else if (str == "break") addToken(TokenType::BREAK);
    else if (str == "continue") addToken(TokenType::CONTINUE);
    else if (str == "def") addToken(TokenType::DEF);
    else if (str == "return") addToken(TokenType::RETURN);
    else if (str == "import") addToken(TokenType::IMPORT);
    else if (str == "switch") addToken(TokenType::SWITCH);
    else if (str == "case") addToken(TokenType::CASE);
    else if (str == "default") addToken(TokenType::DEFAULT);
    else if (str == "try") addToken(TokenType::TRY);
    else if (str == "throw") addToken(TokenType::THROW);
    else if (str == "catch") addToken(TokenType::CATCH);
    else if (str == "class") addToken(TokenType::CLASS);
    else if (str == "new") addToken(TokenType::NEW);
    else addToken(TokenType::WORD, str);
}

void Lexer::tokenizeComment(){
    char current = peek(0);
    while(true){
        if (current == '\r' || current == '\n' || current == '\0') break;
        current = next();
    }
}

void Lexer::tokenizeMultilineComment(){
    char current = peek(0);
    while(true){
        if (current == '\0') error("Reached end of file while parsing multiline comment");
        if (current == '*' && peek(1) == '/') break;
        current = next();
    }
    next(); /// *
    next(); /// /
}

void Lexer::addToken(TokenType type){
    tokens.push_back(new Token(type, "", row, col));
}

void Lexer::addToken(TokenType type, std::string text){
    tokens.push_back(new Token(type, text, row, col));
}

char Lexer::next(){
    ++pos;
    char result = peek(0);
    if (result == '\n'){
        ++row;
        col = 1;
    }
    else ++col;
    return result;
}

char Lexer::peek(int position){
    int now = pos + position;
    if (now >= length) return '\0';
    else return input[now];
}

LexerException* Lexer::error(std::string text){
    return new LexerException(text, row, col);
}
