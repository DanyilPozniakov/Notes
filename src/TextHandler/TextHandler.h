#ifndef TEXTHANDLER_H
#define TEXTHANDLER_H

#include <QObject>
#include <QChar>
#include <QVariantList>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextOption>

#include <memory>

#include "SyntaxHighlighter.h"

using namespace TextEditor;

class TextHandler : public QObject
{
    Q_OBJECT

public:
    QVariantList getCurrentSuggestions() const;

    TextHandler(QObject* parent = nullptr);

    Q_PROPERTY(QVariantList currentSuggestions READ getCurrentSuggestions NOTIFY currentSuggestionsChanged);
    Q_PROPERTY(int m_cursor READ cursorPosition WRITE setCursorPosition NOTIFY cursorUpdated);
    void setTextDocument(QObject* textEditObject);

    void setCursorPosition(int position);
    int cursorPosition() const;

    Q_INVOKABLE void formatCode();

signals:
    void currentSuggestionsChanged();
    void cursorUpdated(int position);

public slots:
    void onTextChanged(int position, int charsRemoved, int charsAdded);
    bool onHandleKeyPress(int key, Qt::KeyboardModifier modifier);

private:
    //std::unique_ptr<QSet<QString>>  m_autoCompleteSet;

    QString m_previousText;
    QTextCursor m_cursor;
    QTextOption m_textOptions;
    QVariantList m_currentSuggestions;

    std::unique_ptr<SyntaxHighlighter> m_syntaxHighlighter;
    QTextDocument* m_textDocument;

    //PRIVATE METHODS
    std::unique_ptr<QSet<QString>> createAutoCompleteSet();

    QString getCurrentLineText() const;
    QString generateIndentation();
    std::size_t getCurrentScope();

    bool isShuldBreakLine(const QString& line);
    bool isLineBeforeBackspaceEmpty();
    bool isLineEmpty(const QString& line);
    void autoCompleteBrackets(const QChar& bracket);
    void autoDeleteBrackets(const QChar& bracket);
    void deleteAllBeforeFirstChar();
    void highlightingMatchingBrackets();
    void findMatchingBracket();
    std::optional<QChar> isBracket(const QChar& bracket);
};

#endif // TEXTHANDLER_H
