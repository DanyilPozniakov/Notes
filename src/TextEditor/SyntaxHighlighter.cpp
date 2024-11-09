#include <QTextCharFormat>

#include "../Parsers/JsonParser.hpp"
#include "SyntaxHighlighter.h"

SyntaxHighlighter::SyntaxHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    QColor color = "#cc7a46";
    keywordFormat.setForeground(color);
    keywordFormat.setFontWeight(QFont::Bold);

    QStringList patterns = JsonParser::parseJsonArray(":/keywords.json");
    for (const auto& pattern : patterns)
    {
        QString paternn = "\\b" + pattern + "\\b";
        HighlightingRule rule;
        rule.pattern = QRegularExpression(paternn);
        rule.format = keywordFormat;
        rules.append(rule);
    }
    qDebug() << "SyntaxHighlighter created";
}

void SyntaxHighlighter::highlightBlock(const QString &text)
{
    for(const auto& rule : rules)
    {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext())
        {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
    qDebug() << "highlightBlock";


}
