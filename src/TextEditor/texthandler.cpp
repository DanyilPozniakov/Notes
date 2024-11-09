#include <QMap>
#include <QDebug>
#include <QStack>
#include <QRegularExpression>
#include <QQuickTextDocument>
#include <QTextCursor>
#include <QTextBlock>
#include "src/parsers/JsonParser.hpp"
#include "src/TextEditor/Regex.hpp"

#include <QQuickTextDocument>
#include <iostream>

#include "texthandler.h"

//TODO: real-time log for debugging in application

static const QMap<QChar,QChar> autoCharMap = {
    {'(',')'},
    {'{','}'},
    {'[',']'},
    {'<','>'}
};





TextHandler::TextHandler(QObject *parent) : QObject(parent)
{
    m_autoCompleteSet = createAutoCompleteSet();

}

std::unique_ptr<QSet<QString>> TextHandler::createAutoCompleteSet()
{

    return {};
}

QVariantList TextHandler::getCurrentSuggestions() const
{
    return m_currentSuggestions;
}

void TextHandler::setTextDocument(QObject *textEditObject)
{
    if(!textEditObject)
    {
        assert(textEditObject && "TextEditObject is null");
        return;
    }
    QVariant docVariant = textEditObject->property("textDocument");
    QQuickTextDocument *quickDoc = qvariant_cast<QQuickTextDocument*>(docVariant);
    if (quickDoc) {
        assert(quickDoc && "TextDocument is null");
        m_textDocument = quickDoc->textDocument();
        connect(m_textDocument, &QTextDocument::contentsChange, this, &TextHandler::onTextChanged);
        //TODO: отдельный метод для установки опций
        m_textOptions =  m_textDocument->defaultTextOption();
        m_textOptions.setTabStopDistance(25);
        m_textDocument->setDefaultTextOption(m_textOptions);

        //CURSOR
        m_cursor = QTextCursor(m_textDocument);
        m_cursor.setPosition(0);

        //SYNTAX HIGHLIGHTER
        m_syntaxHighlighter = new SyntaxHighlighter(m_textDocument);
    }
}



void TextHandler::onTextChanged(int position, int charsRemoved, int charsAdded)
{

    ///TODO: RESTRUCTURE THIS FUNCTION
    if(!m_textDocument) assert(m_textDocument && "TextDocument is null");
    if(m_isAutoCompleting) return;

    //autocomplete brackets
    QString text = m_textDocument->toPlainText().mid(position, charsAdded);
    QString deletedText = m_previousText.mid(position,1);
    if(!text.isEmpty() && autoCharMap.contains(text[0]))
    {
        autoCompleteBrackets(text[0]);
    }

    //autodetect brackets
    if(charsRemoved == 1 && !deletedText.isEmpty() && isBracket(deletedText[0]))
    {
        autoDeleteBrackets(deletedText[0]);
    }

    m_previousText = m_textDocument->toPlainText();
}




QString TextHandler::getCurrentLineText()
{
    QTextBlock  block = m_cursor.block();
    return block.text();
}



std::optional<QChar> TextHandler::isBracket(const QChar &bracket)
{
    if(autoCharMap.find(bracket) != autoCharMap.end())
    {
        return bracket;
    }
    return std::nullopt;
}

void TextHandler::autoCompleteBrackets(const QChar& bracket)
{
    m_isAutoCompleting = true;
    QChar closingBracket = autoCharMap[bracket];
    m_cursor.insertText(closingBracket);
    m_cursor.movePosition(QTextCursor::Left,QTextCursor::MoveAnchor,1);
    emit cursorUpdated(m_cursor.position());
    m_isAutoCompleting = false;

}

void TextHandler::autoDeleteBrackets(const QChar &bracket)
{
    QString textAfterBracket = m_previousText.mid(m_cursor.position());
    QChar closingBracket = autoCharMap[bracket];
    int stack = 0;
    int iter = 0;
    for(auto ch : textAfterBracket)
    {
        if(ch == bracket)
        {
            stack++;
        }
        if(ch == closingBracket)
        {
            stack--;
            if(stack == 0)
            {
                int position = m_cursor.position() + iter;
                qDebug() << "Position to delete: " << position;
                m_cursor.setPosition(position);
                m_cursor.deletePreviousChar();
            }
        }
        ++iter;
    }
}

int TextHandler::cursorPosition() const
{
    qDebug() << "Getting cursor position: " << m_cursor.position();
    return m_cursor.position();
}
void TextHandler::setCursorPosition(int position)
{
    qDebug() << "Setting cursor position: " << position;
    m_cursor.setPosition(position);
}


bool TextHandler::onHandleKeyPress(int key, Qt::KeyboardModifier modifier)
{
    switch (key)
    {

        ///RETURN
        case Qt::Key_Return:
        {
            QString line = getCurrentLineText();
            if(line.contains("{}"))
            {
                if(shuldBreakLine(line))
                {
                    //TODO: добавить отстуцпы если есть внешкий скоупrtyj
                    QString indentation = generateIndentation();
                    QString indentationMin = generateIndentation().removeLast();
                    m_cursor.movePosition(QTextCursor::Left,QTextCursor::MoveAnchor,1);
                    m_cursor.insertText("\n" + indentationMin);
                    QString text =  "\n" + indentation + "\n" + indentationMin;
                    m_cursor.insertText(text);
                    m_cursor.movePosition(QTextCursor::Left,QTextCursor::MoveAnchor,getCurrentScope());
                    emit cursorUpdated(m_cursor.position());
                    return true;
                }
                else
                {
                    QString indentation = generateIndentation();
                    QString text = "\n" + indentation + "\n";
                    m_cursor.insertText(text);
                    m_cursor.insertText(indentation.removeLast());
                    m_cursor.movePosition(QTextCursor::Left,QTextCursor::MoveAnchor,getCurrentScope());
                    emit cursorUpdated(m_cursor.position());
                    return true;
                }
            }



            m_cursor.insertText("\n");
            m_cursor.insertText(generateIndentation());
            //m_cursor.movePosition(QTextCursor::Left,QTextCursor::MoveAnchor,2);
            //emit cursorUpdated(m_cursor.position());
            return true;
        }

        /// BACKSPACE
        case Qt::Key_Backspace:
        {
            //TODO: implement backspace
            //TODO: добавить проверку на пустую строку
            if(isLineBeforeBackspaceEmpty())
            {
                deleteAllBeforeFirstChar();
                return true;
            }
        }
    }
    return false;
}
bool TextHandler::shuldBreakLine(const QString& line)
{
    if(line.isEmpty()) return false;
    QRegularExpression classRegex(Regex::CLASS_DECLARATION);
    QRegularExpression funcRegex(Regex::FUNCTION_DECLARATION);
    if(classRegex.match(line).hasMatch() || funcRegex.match(line).hasMatch())
    {
        return true;
    }
    return false;
}
std::size_t TextHandler::getCurrentScope()
{
     QString text = m_textDocument->toPlainText();
     QString subStr = text.left(m_cursor.position());
     std::size_t scope = 0;
     for(auto ch : subStr)
     {
         if(ch == '{')
         {
             ++scope;
         }
         if(ch == '}')
         {
             --scope;
         }
     }
     return scope;
}

QString TextHandler::generateIndentation()
{
    const std::size_t scope = getCurrentScope();
    QString indentation;
    for (std::size_t i = 0; i < scope; ++i)
    {
        indentation += "\t";
    }
    return indentation;
}


///FINAL
bool TextHandler::isLineBeforeBackspaceEmpty()
{
    QString leftText = m_previousText.left(m_cursor.position());
    for(auto ch = leftText.rbegin(); ch != leftText.rend(); ++ch)
    {
        if(*ch == '\n')
        {
            return true;
        }
        if(*ch != ' ' && *ch != '\t')
        {
            return false;
        }
    }
    return false;
}
void TextHandler::deleteAllBeforeFirstChar()
{
    QString leftText = m_previousText.left(m_cursor.position());
    QTextBlock block = m_cursor.block();
    QTextBlock previousBlock = block.previous();
    if (previousBlock.isValid() && isLineEmpty(previousBlock.text())) {
        qDebug() << "Previous block is empty";
        m_cursor.movePosition(QTextCursor::Up, QTextCursor::KeepAnchor, 1);
        m_cursor.removeSelectedText();
        emit cursorUpdated(m_cursor.position());
        return;
    }

    for (auto ch = leftText.rbegin(); ch != leftText.rend(); ++ch)
    {
        if (*ch == ' ' || *ch == '\t' || *ch == '\n')
        {
            m_cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, 1);
        }
        else break;
    }
    if (m_cursor.hasSelection()) {
        m_cursor.removeSelectedText();
        emit cursorUpdated(m_cursor.position());
    }
}
bool TextHandler::isLineEmpty(const QString &line)
{
    return line.trimmed().isEmpty();
}







