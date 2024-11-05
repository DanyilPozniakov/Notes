#ifndef REGEX_HPP
#define REGEX_HPP

#include <QString>

namespace Regex
{
    const QString CLASS_DECLARATION = R"(^\s*(class)\s+(\w+)(\s*)({))";
    const QString FUNCTION_DECLARATION = R"(\w+\s+w+\s*(\(\s*\))\s*({))";
}

#endif //REGEX_HPP
