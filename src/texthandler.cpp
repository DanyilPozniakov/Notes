#include <QMap>
#include <QDebug>
#include <QStack>
#include "../src/parsers/JsonParser.hpp"
#include "texthandler.h"


 static const QMap<QChar,QChar> autoCharMap = {
    {'(',')'},
    {'{','}'},
    {'[',']'},
    {'"','"'},
    {'\'','\''},
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
    qDebug() << "Key: " << eventText;
    switch (key) {
        case Qt::Key_Backspace:
        {
            if(cursorPosition == 0) return false;
            QChar charToDelete = text.at(cursorPosition - 1);
            if(auto endChar = isAutoChar(charToDelete))
            {
                deleteBracketPair(charToDelete,endChar.value(),text,cursorPosition);
                return true;
            }
        }
        case Qt::Key_Return:
        {
            break;
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
            if(eventText.isEmpty())
            {
                return false;
            }
            else if(auto ch = isAutoChar(eventText.front()))
            {
                completeBracket(eventText,ch.value(), cursorPosition);
                return true;
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
QString TextHandler::getAutocompleteSuggestions(QString currentWord)
{
    return QString();
}
QString TextHandler::autoIndent(QString text)
{
    return QString();
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






