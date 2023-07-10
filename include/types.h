#ifndef TYPES_H
#define TYPES_H

#include <map>
#include <variant>  // C++ 17
#include <string>

typedef std::map<std::string, std::variant<int, float, std::string>> VariantMap_T;

#endif

