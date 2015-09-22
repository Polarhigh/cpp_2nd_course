// Автор: ;
// Дата: 2015г

//Задание:
//Разработать программу, которая должна сделать следующее :
//1. Прочитать содержимое текстового файла.Файл может содержать :
//a.Слова – состоят из латинских строчных и заглавных букв, а также цифр, длинна слова должна быть не более 20 символов
//b.Знаки препинания – «.», «, » «!» « ? » « : » «; »
//c.Пробельные символы – пробел, табуляция, символ новой строки.
//
//2. Отформатировать текст следующим образом :
//a.Не должно быть  пробельных символов отличных от пробела
//b.Не должно идти подряд более одного пробела
//c.Между словом и знаком препинания не должно быть пробела
//d.После знака препинания всегда должен идти пробел
//e.Слова длиной более 10 символов заменяются на слово «Vau!!!»
//
//3. Преобразовать полученный текст в набор строка, каждая из которых содержит целое количество строк(слово должно целиком находиться в строке) и ее длинна не превышает 40 символов.

#include <iostream>
#include <sstream>
#include <fstream>
#include <locale>
#include <codecvt>
#include <string>
#include <map>
#include <vector>
#include "lex_utils.h"

using namespace std;
using namespace lex;

const int UTF8_MAGIC = 0x10ffff;

enum class Lexeme
{
    WORD,
    PUNCT_MARK,
    SPACE,
    TABULATION,
    NEWLINE,
    UNKNOWN
};

// специальный функтор для transform, позволяет выводить не более 40 символов на строку без разрыва слов
struct NewlineFunct : unary_function<token_t<Lexeme>, wstring>
{
    int curLen = 0;

    wstring operator()(const token_t<Lexeme>& tok)
    {
        if (tok.value.length() + curLen >= 40)
        {
            curLen = tok.value.length();
            return L"\n" + tok.value;
        }
        else
        {
            curLen += tok.value.length();
            return tok.value;
        }
    }
};

void ApplyRules(vector<token_t<Lexeme>>& tokens)
{
    // ## требуется 1 токен
    // замена табуляции и пероносов строк
    replace_if(tokens.begin(), tokens.end(), [](const token_t<Lexeme>& tok) { return tok.lexeme == Lexeme::NEWLINE || tok.lexeme == Lexeme::TABULATION; }, token_t<Lexeme>(Lexeme::SPACE, L" "));

    //замена слова длинной более 10 символов на Vau!!!
    replace_if(tokens.begin(), tokens.end(), [](const token_t<Lexeme>& tok) { return tok.lexeme == Lexeme::WORD && tok.value.length() > 10; }, token_t<Lexeme>(Lexeme::WORD, L"Vau!!!"));

    // ## требуется 2 токена
    if (tokens.size() > 1)
    {
        // удаление нескольких пробелов идущих подряд
        tokens.erase(unique(tokens.begin(), tokens.end(), [](const token_t<Lexeme>& lhs, const token_t<Lexeme>& rhs) { return lhs.lexeme == Lexeme::SPACE && lhs.lexeme == rhs.lexeme; }), tokens.end());

        //добавление пробела после знака препинания
        Lexeme prevLex, curLex, nextLex;
        for (auto it = tokens.begin(); it != tokens.end() - 1; ++it)
        {
            curLex = (*it).lexeme;
            nextLex = (*(it + 1)).lexeme;

            if (curLex == Lexeme::PUNCT_MARK && nextLex != Lexeme::SPACE)
                it = tokens.insert(it + 1, token_t<Lexeme>(Lexeme::SPACE, L" "));
        }

        // ## требуется 3 токена
        if (tokens.size() > 2)
        {
            // удаление пробела между словом и знаком препинания
            for (auto it = tokens.begin() + 1; it != tokens.end() - 1;)
            {
                prevLex = (*(it - 1)).lexeme;
                curLex = (*it).lexeme;
                nextLex = (*(it + 1)).lexeme;

                if (prevLex == Lexeme::WORD && curLex == Lexeme::SPACE && nextLex == Lexeme::PUNCT_MARK)
                    it = tokens.erase(it);
                else
                    ++it;
            }
        }
    }
}

void FileToString(const wchar_t* file, wstring& outText)
{
    wifstream wif;
    wstringstream wss;

    wif.open(file, ios_base::in);
    if (wif.is_open())
    {
        wif.imbue(locale(wif.getloc(), new codecvt_utf8<wchar_t, UTF8_MAGIC, consume_header>()));
        wss << wif.rdbuf();
        outText = wss.str();
    }
}

int main()
{
    locale::global(locale(""));

    wstring text;
    vector<token_t<Lexeme>> tokens;
    map<Lexeme, wregex> lexRules =
    {
        { Lexeme::WORD,			wregex(L"[a-zA-Zа-яА-Я]+") },
        { Lexeme::PUNCT_MARK,	wregex(L"[\\.,!\\?:;]") },
        { Lexeme::SPACE,		wregex(L" ") },
        { Lexeme::TABULATION,	wregex(L"\\t") },
        { Lexeme::NEWLINE,		wregex(L"\\n") },
    };

    FileToString(L"main.cpp", text);

    wcout << L"[Исходный текст]" << endl;
    wcout << text << endl << endl << endl;

    LexParse(text, lexRules, tokens); // в Debug сборке время парсинга > 1с
    ApplyRules(tokens);
    TokensToString(tokens, text);

    wcout << L"[Преобразованный текст]" << endl;
    vector<wstring> stext;
    transform(tokens.begin(), tokens.end(), back_inserter(stext), NewlineFunct());
    
    copy(stext.begin(), stext.end(), ostream_iterator<wstring, wchar_t>(wcout, L""));
    wcout << endl;

    return 0;
}