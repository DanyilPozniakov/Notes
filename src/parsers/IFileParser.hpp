#ifndef IFILEPARSER_HPP
#define IFILEPARSER_HPP
#include <QString>

class IFileParser
{
public:
    virtual void parseFile(const QString& path) = 0;
    virtual ~IFileParser() = default;
};


#endif //IFILEPARSER_HPP
