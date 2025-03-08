#include "decoder.h"
#include <iostream>
std::string HtmlDecode(const std::string& html)
{
    //find
    const std::map<std::string, char> entities =
    {
        {"&quot;", '"'},
        {"&apos;", '\''},
        {"&lt;", '<'},
        {"&gt;", '>'},
        {"&amp;", '&'}
    };

    std::string result;
    result.reserve(html.length());

    for (size_t i = 0; i < html.length(); ++i)
    {
        if (html[i] == '&')
        {
            bool found = false;
            for (const auto& [entity, replacement] : entities)
            {
                if (html.compare(i, entity.length(), entity) == 0)
                {
                    result += replacement;
                    i += entity.length() - 1;
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                result += html[i];
            }
        }
        else
        {
            result += html[i];
        }
    }
    
    return result;
}
