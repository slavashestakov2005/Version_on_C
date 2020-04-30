#include "path.h"
#include "Lib/string.h"
std::vector<std::string> Path::pathes = {};
bool Path::import = true;
Array* Path::arguments = nullptr;
void Path::setPath(std::string path){
    pathes.push_back(path);
}
std::string Path::getPath(){
    return pathes.back();
}
void Path::popPath(){
    pathes.pop_back();
}
bool Path::getImpoted(){
    return import;
}
void Path::setImpoted(bool imp){
    import = imp;
}
void Path::setCommandArguments(std::vector<std::string> argv){
    arguments = new Array(argv.size());
    for(int i = 0; i < argv.size(); ++i) arguments -> set(i, new String(argv[i]));
}
Array* Path::getCommandArguments(){
    return arguments;
}
