#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QString>

class SyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit SyntaxHighlighter(QTextDocument* parent = nullptr);

    void highlightBlock(const QString& text) override;


private:
    //QString patterns;
    QTextCharFormat keywordFormat;
    struct HighlightingRule
    {
        QRegularExpression  pattern = QRegularExpression("\\bclass\\b");
        QTextCharFormat     format;
    };
    QVector<HighlightingRule> rules;

};

#endif //SYNTAXHIGHLIGHTER_H
