#include "parseexception.h"

const char* ParseException::what() const noexcept{
    return text.c_str();
}
