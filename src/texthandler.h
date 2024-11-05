#ifndef TEXTHANDLER_H
#define TEXTHANDLER_H

#include <QObject>
#include <QChar>
#include <QVariantList>
#include <QTextDocument>

class TextHandler : public QObject
{
    Q_OBJECT

public:
    TextHandler(QObject *parent = nullptr);

    Q_PROPERTY(QVariantList currentSuggestions READ getCurrentSuggestions NOTIFY currentSuggestionsChanged);
    QVariantList getCurrentSuggestions() const;

    Q_INVOKABLE bool handleKeyPress(const int& key, const QString& eventText,const QString &text, int cursorPosition);
    void completeBracket(const QString& firstChar,const QString& endChar, int cursorPosition);
    void deleteBracketPair(QChar& ch,QChar& endChar, const QString& text,  int cursorPos);
    void autoFormatBracketPair(int cursorPos);


    Q_INVOKABLE bool autocompleteSuggestions(QString currentWord);
    QString autoIndent(QString text);



signals:
    void insertText(int cursorPosition, const QString &text);
    void deleteText(int start, int end);
    void updateCursorPosition(int cursorPosition);
    void currentSuggestionsChanged();


private:
    QTextDocument*                  m_textDocument;
    QString                         m_text;

    std::unique_ptr<QSet<QString>>  m_autoCompleteSet;
    QVariantList                    m_currentSuggestions;

    std::optional<QChar>            isAutoChar(const QChar &text);
    std::unique_ptr<QSet<QString>>  createAutoCompleteSet();

    QString getCurrentLine(const QString& text, int cursorPosition);

    bool shouldLineBreak (const QString& line);
    bool isBracketPair(const QString& text, int cursorPos);

public:
    void setTextDocument(QObject* textEditObject);
};

#endif // TEXTHANDLER_H