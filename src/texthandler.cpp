#include <QMap>
#include <QDebug>
#include <QStack>
#include <QRegularExpression>
#include <QQuickTextDocument>
#include "../src/parsers/JsonParser.hpp"
#include "Regex.hpp"

#include <QQuickTextDocument>

#include "texthandler.h"


//TODO: real-time log for debugging in application

static const QMap<QChar,QChar> autoCharMap = {
    {'(',')'},
    {'{','}'},
    {'[',']'},
    {'"','"'},
    {'\'','\''}
};



TextHandler::TextHandler(QObject *parent) : QObject(parent)
{
    m_autoCompleteSet = createAutoCompleteSet();
}

std::optional<QChar> TextHandler::isAutoChar(const QChar &text)
{
    if(auto value = autoCharMap.find(text); value != autoCharMap.end())
    {
        return value.value();
    }
    return std::nullopt;
}

bool TextHandler::handleKeyPress(const int& key, const QString& eventText,const QString &text, int cursorPosition)
{
    m_text = text;
    switch (key) {
        case Qt::Key_Backspace:
        {
            {
                /**
                *      @brief delete pair logic for brackets
                *      @see deleteBracketPair()
                *  **/
                if(cursorPosition == 0) return false;
                QChar charToDelete = text.at(cursorPosition - 1);
                if(auto endChar = isAutoChar(charToDelete))
                {
                    deleteBracketPair(charToDelete,endChar.value(),text,cursorPosition);
                    return true;
                }
            }
            break;
        }
        case Qt::Key_Return:
        {
            {
                //TODO: AUTOFORMAT LOGIC
                if(isBracketPair(text,cursorPosition))
                {
                    autoFormatBracketPair(cursorPosition);
                    return true;
                }

                return false;
            }
        }
        case Qt::Key_Tab:
        {
            break;
        }
        case Qt::Key_Shift:
        {
            break;
        }
        default:
        {
            if(eventText.isEmpty()) return false;
            //TODO: Add more key events...

            {
                /**
                *      @brief autoComplete logic for brackets
                *      @see completeBracket()
                *  **/
                if(auto ch = isAutoChar(eventText.front()))
                {
                    completeBracket(eventText,ch.value(), cursorPosition);
                    return true;
                }
            }

        }
    }
    return false;
}



void TextHandler::completeBracket(const QString& firstChar,const QString& endChar, int cursorPosition)
{
    emit insertText(cursorPosition, QString(firstChar) + QString(endChar));
    emit updateCursorPosition(cursorPosition + 1);
}

void TextHandler::deleteBracketPair(QChar& ch,QChar& endChar, const QString& text,  int cursorPos)
{
    auto textLength = text.length();
    int position = cursorPos;
    int stack = 0;

    while (position < textLength)
    {
        QChar currentChar = text.at(position);
        if (currentChar == ch)
        {
            stack++;
        }
        else if (currentChar == endChar)
        {
            if (stack == 0)
            {
                emit deleteText(position, position + 1);
                emit deleteText(cursorPos - 1, cursorPos);
                return;
            }
            else
            {
                stack--;
            }
        }
        position++;
    }
    emit deleteText(cursorPos - 1, cursorPos);
}

void TextHandler::autoFormatBracketPair(int cursorPos)
{
    emit deleteText(cursorPos - 1, cursorPos + 1);
    if(shouldLineBreak(getCurrentLine(m_text,cursorPos)))
    {
        emit insertText(cursorPos - 1, "\n");
        ++cursorPos;
    }
    emit insertText(0,"{\n\t\n}");
    emit updateCursorPosition(cursorPos + 2);
}


bool TextHandler::autocompleteSuggestions(QString currentWord)
{
    m_currentSuggestions.clear();

    if (currentWord.isEmpty())
    {
        return false;
    }

    if (m_autoCompleteSet)
    {
        for (const auto& word : *m_autoCompleteSet)
        {
            if (word.startsWith(currentWord))
            {
                m_currentSuggestions.append(word);
            }
        }
        emit currentSuggestionsChanged();
        return !m_currentSuggestions.isEmpty();
    }
    return false;
}




std::unique_ptr<QSet<QString>> TextHandler::createAutoCompleteSet()
{
    auto set = JsonParser::parseAutocompleteJsonArray(":/keywords.json");
    if(set)
    {
        return std::make_unique<QSet<QString>>(std::move(*set));
    }
    qDebug() << "Error parsing autocomplete json file";
    return {};
}

QVariantList TextHandler::getCurrentSuggestions() const
{
    return m_currentSuggestions;
}

QString TextHandler::getCurrentLine(const QString &text, int cursorPosition)
{
    if(text.isEmpty() || cursorPosition < 0 || cursorPosition > text.length()) return {};
    int start   = text.lastIndexOf('\n',cursorPosition - 1);
    int end     = text.indexOf('\n',cursorPosition);

    if(start == -1) start = 0;
    else start += 1;

    if(end == -1) end = text.length();

    int length = end - start;
    return text.sliced(start,length);
}

bool TextHandler::shouldLineBreak(const QString &line)
{
    if(line.isEmpty()) return false;

    QRegularExpression classRe(Regex::CLASS_DECLARATION);
    QRegularExpression funcRe(Regex::FUNCTION_DECLARATION);
    if(classRe.match(line).hasMatch() || funcRe.match(line).hasMatch())
    {
        return true;
    }
    return false;
}

bool TextHandler::isBracketPair(const QString &text, int cursorPos)
{
    if(cursorPos == 0 || cursorPos > text.length()) return false;
    if(text[cursorPos - 1] == '{' && text[cursorPos] == '}')
    {
        return true;
    }
    return false;
}

void TextHandler::setTextDocument(QObject *textEditObject)
{
    if(!textEditObject)
    {
        //TODO: error handling
        return;
    }
    QVariant docVariant = textEditObject->property("textDocument");
    QQuickTextDocument *quickDoc = qvariant_cast<QQuickTextDocument*>(docVariant);
    if (quickDoc) {
        m_textDocument = quickDoc->textDocument();
    }
}









