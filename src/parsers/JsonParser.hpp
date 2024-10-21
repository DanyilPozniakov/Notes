#ifndef JSONPARSER_HPP
#define JSONPARSER_HPP

#include <optional>
#include <QSet>
#include <QString>
#include "IFileParser.hpp"

class JsonParser : public IFileParser
{
public:
    virtual void parseFile(const QString& path) override;
    static QSet<QString>* parseAutocompleteJsonArray(const QString& path);
};

#endif //JSONPARSER_HPP

