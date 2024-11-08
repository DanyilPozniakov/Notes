#ifndef REGEX_HPP
#define REGEX_HPP

#include <QString>

namespace Regex
{
    const QString CLASS_DECLARATION = R"(^\s*(class)\s+(\w+)(\s*)({))";
    const QString FUNCTION_DECLARATION = R"(^\s*\w+\s+w+\s*(\(\s*\w*\s*\w*\))\s*({))";
}
void add(int a) {}
#endif //REGEX_HPP
