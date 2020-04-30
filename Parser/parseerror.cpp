#include "parseerror.h"
#include <sstream>
int ParseError::getLine(){
    return line;
}
std::exception* ParseError::getException(){
    return exception;
}
ParseError::operator std::string(){
    std::ostringstream os;
    os << "ParseError on line " << line << ": " << exception -> what();
    return os.str();
}
