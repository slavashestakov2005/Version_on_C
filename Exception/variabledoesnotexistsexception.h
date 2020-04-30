#ifndef VARIABLEDOESNOTEXISTSEXCEPTION_H_INCLUDED
#define VARIABLEDOESNOTEXISTSEXCEPTION_H_INCLUDED

#include <string>
class VariableDoesNotExistsException : public std::exception{
private:
    std::string text;
public:
    explicit VariableDoesNotExistsException (std::string text) : text(text) {}
    const char* what() const noexcept { return ("Variable " + text + " does not exists").c_str(); }
    std::string getText(){ return text; }
    virtual ~VariableDoesNotExistsException () noexcept {}
};

#endif // VARIABLEDOESNOTEXISTSEXCEPTION_H_INCLUDED
