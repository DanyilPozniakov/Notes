#ifndef TEXTHANDLER_H
#define TEXTHANDLER_H

#include <QObject>
#include <QChar>

class TextHandler : public QObject
{
    Q_OBJECT
public:
    TextHandler();

    Q_INVOKABLE QString completeBracket(const QChar ch);
    Q_INVOKABLE int     deleteBracketPair(const QChar ch,const QString text);
    Q_INVOKABLE QString getAutocompleteSuggestions(QString currentWord);   // get the autocomplete suggestions
    Q_INVOKABLE QString autoIndent(QString text);                           // auto indent the text


};

#endif // TEXTHANDLER_H
