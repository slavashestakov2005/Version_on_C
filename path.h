#ifndef PATH_H_INCLUDED
#define PATH_H_INCLUDED

#include <string>
#include <vector>
#include "Lib/array.h"
class Path{
private:
    static std::vector<std::string> pathes;
    static bool import;
    static Array* arguments;
public:
    static void setPath(std::string path);
    static std::string getPath();
    static void popPath();
    static bool getImpoted();
    static void setImpoted(bool imp);
    static void setCommandArguments(std::vector<std::string> argv);
    static Array* getCommandArguments();
};

#endif // PATH_H_INCLUDED
