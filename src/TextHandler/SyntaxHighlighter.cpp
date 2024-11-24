#include <QTextCharFormat>

#include "../Parsers/JsonParser.h"
#include "SyntaxHighlighter.h"

TextEditor::SyntaxHighlighter::SyntaxHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    assert(parent && "TextDocument is null in syntaxHighlighter constructor");
    QColor color = "#cc7a46";
    keywordFormat.setForeground(color);
    keywordFormat.setFontWeight(QFont::Bold);

    QStringList patterns = JsonParser::parseKeywords();
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

void TextEditor::SyntaxHighlighter::highlightBlock(const QString &text)
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

