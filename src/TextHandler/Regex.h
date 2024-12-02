#ifndef REGEX_HPP
#define REGEX_HPP

#include <QString>

namespace Regex
{
    const static QString CLASS_DECLARATION = R"(^\s*(class)\s+(\w+)(\s*)({))";
    const static QString FUNCTION_DECLARATION = R"(^\s*\w+\s+\w+\s*\((\w*(<\w*(::\w+)*>))*(\s*[\&\*]?\w+\,?\s?)*\)\s*\{)";
    const static QString COMMENT = R"(\/\/.*$)";  //only words and digits
}

#endif //REGEX_HPP
