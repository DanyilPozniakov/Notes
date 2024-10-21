#ifndef TEXTHANDLER_H
#define TEXTHANDLER_H

#include <QObject>
#include <QChar>

class TextHandler : public QObject
{
    Q_OBJECT

public:
    TextHandler(QObject *parent = nullptr);

    std::optional<QChar> isAutoChar(const QChar &text);
    Q_INVOKABLE bool handleKeyPress(const int& key, const QString& eventText,const QString &text, int cursorPosition);
    void completeBracket(const QString& firstChar,const QString& endChar, int cursorPosition);
    void deleteBracketPair(QChar& ch,QChar& endChar, const QString& text,  int cursorPos);


    QString getAutocompleteSuggestions(QString currentWord);
    QString autoIndent(QString text);



signals:
    void insertText(int cursorPosition, const QString &text);
    void deleteText(int start, int end);
    void updateCursorPosition(int cursorPosition);


private:
    std::unique_ptr<QSet<QString>> m_autoCompleteSet;

    std::unique_ptr<QSet<QString>> createAutoCompleteSet();
};

#endif // TEXTHANDLER_H