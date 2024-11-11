#ifndef TEXTHANDLER_H
#define TEXTHANDLER_H

#include <QObject>
#include <QChar>
#include <QVariantList>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextOption>

#include "SyntaxHighlighter.h"

using namespace TextEditor;


class TextHandler : public QObject
{
    Q_OBJECT

public:
    QVariantList getCurrentSuggestions() const;
    Q_PROPERTY(QVariantList currentSuggestions READ getCurrentSuggestions NOTIFY currentSuggestionsChanged);
    Q_PROPERTY(int m_cursor READ cursorPosition WRITE setCursorPosition NOTIFY cursorUpdated);
    TextHandler(QObject *parent = nullptr);

    int cursorPosition() const;
    void setCursorPosition(int position);


signals:
    void currentSuggestionsChanged();
    void cursorUpdated(int position);


public slots:
    void onTextChanged(int position, int charsRemoved, int charsAdded);
    bool onHandleKeyPress(int key, Qt::KeyboardModifier modifier);

private:
    QString                         m_previousText;
    QTextCursor                     m_cursor;
    QTextDocument*                  m_textDocument;
    QTextOption                     m_textOptions;
    std::unique_ptr<QSet<QString>>  m_autoCompleteSet;
    QVariantList                    m_currentSuggestions;

    SyntaxHighlighter*              m_syntaxHighlighter;

    bool m_isAutoCompleting = false;


    std::unique_ptr<QSet<QString>>  createAutoCompleteSet();

    QString getCurrentLineText();
    std::size_t getCurrentScope();
    QString generateIndentation();


    bool shuldBreakLine(const QString& line);
    bool isLineBeforeBackspaceEmpty();
    bool isLineEmpty(const QString& line);
    std::optional<QChar> isBracket(const QChar& bracket);

    void autoCompleteBrackets(const QChar& bracket);
    void autoDeleteBrackets(const QChar& bracket);
    void deleteAllBeforeFirstChar();




public:
    void setTextDocument(QObject* textEditObject);
};

#endif // TEXTHANDLER_H
