#include <map>
#include <QDebug>
#include <QStack>
#include "texthandler.h"

 static const std::map<QChar,QChar> autoCharMap = {
    {'(',')'},
    {'{','}'},
    {'[',']'},
    {'"','"'},
    {'\'','\''},
};



TextHandler::TextHandler() {}

QString TextHandler::completeBracket(const QChar ch)
{
    if(auto value = autoCharMap.find(ch); value != autoCharMap.end())
    {
        return value->second;
    }
    return {};
}

int TextHandler::deleteBracketPair(const QChar ch,const QString text)
{
    if(auto value = autoCharMap.find(ch); value != autoCharMap.end()) {
        auto endChar = value->second;
        QStack<QChar> stack;
        for(auto i = 0 ; i < text.size(); ++i)
        {
            if(text[i] == ch)
            {
                stack.push(ch);
            }
            else if(text[i] == endChar)
            {
                if(stack.isEmpty())
                {
                    return i;
                }
                stack.pop();
            }
        }
        return -1;
    }
    else
    {
        return -1;
    }
}
QString TextHandler::getAutocompleteSuggestions(QString currentWord)
{
    return QString();
}
QString TextHandler::autoIndent(QString text)
{
    return QString();
}

