#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QString>

namespace {

struct HighlightingRule
{
  QRegularExpression  pattern;
  QTextCharFormat     format;
};

}

namespace TextEditor {

class SyntaxHighlighter : public QSyntaxHighlighter {
  Q_OBJECT
public:
  explicit SyntaxHighlighter(QTextDocument *parent = nullptr);
  void highlightBlock(const QString &text) override;

private:
  QTextCharFormat keywordFormat;
  QVector<HighlightingRule> rules;
};

} // namespace TextEditor
#endif //SYNTAXHIGHLIGHTER_H
