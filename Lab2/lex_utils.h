#ifndef _LEX_UTILS_H_
#define _LEX_UTILS_H_

#include <regex>
#include <map>
#include <vector>
#include <string>

namespace lex
{
    template<typename T>
    struct token_t
    {
        T lexeme;
        std::wstring value;

        token_t() {}

        token_t(T type, std::wstring token)
        {
            this->lexeme = type;
            this->value = token;
        }

        token_t(T type, wchar_t value)
        {
            this->lexeme = type;
            this->value = value;
        }
    };

    template<typename T>
    void LexParse(const std::wstring& text, const std::map<T, std::wregex>& parseRules, std::vector<token_t<T>>& outTokens)
    {
        std::wsmatch match;

        for (auto itstr = text.begin(); itstr != text.end();)
        {
            for (auto itruls = parseRules.begin(); itruls != parseRules.end(); ++itruls)
            {
                if (std::regex_search(itstr, text.end(), match, itruls->second, std::regex_constants::match_continuous))
                {
                    outTokens.push_back(token_t<T>(itruls->first, match[0]));
                    itstr += match[0].length();
                    break;
                }
            }

            if (match.empty())
            {
                outTokens.push_back(token_t<T>(T::UNKNOWN, *itstr));
                ++itstr;
            }
        }
    }
}

#endif // _LEX_UTILS_H_