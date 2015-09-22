// �����: ;
// ����: 2015�

//�������:
//����������� ���������, ������� ������ ������� ��������� :
//1. ��������� ���������� ���������� �����.���� ����� ��������� :
//a.����� � ������� �� ��������� �������� � ��������� ����, � ����� ����, ������ ����� ������ ���� �� ����� 20 ��������
//b.����� ���������� � �.�, �, � �!� � ? � � : � �; �
//c.���������� ������� � ������, ���������, ������ ����� ������.
//
//2. ��������������� ����� ��������� ������� :
//a.�� ������ ����  ���������� �������� �������� �� �������
//b.�� ������ ���� ������ ����� ������ �������
//c.����� ������ � ������ ���������� �� ������ ���� �������
//d.����� ����� ���������� ������ ������ ���� ������
//e.����� ������ ����� 10 �������� ���������� �� ����� �Vau!!!�
//
//3. ������������� ���������� ����� � ����� ������, ������ �� ������� �������� ����� ���������� �����(����� ������ ������� ���������� � ������) � �� ������ �� ��������� 40 ��������.

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

//const int UTF8_MAGIC = 0x10ffff;

enum class Lexeme
{
	WORD,
	PUNCT_MARK,
	SPACE,
	TABULATION,
	NEWLINE,
	UNKNOWN
};

void ApplyRules(vector<token_t<Lexeme>>& tokens)
{
	// ## ��������� 1 �����
	// ������ ��������� � ��������� �����
	replace_if(tokens.begin(), tokens.end(), [](const token_t<Lexeme>& tok) { return tok.lexeme == Lexeme::NEWLINE || tok.lexeme == Lexeme::TABULATION; }, token_t<Lexeme>(Lexeme::SPACE, L" "));

	//������ ����� ������� ����� 10 �������� �� Vau!!!
	replace_if(tokens.begin(), tokens.end(), [](const token_t<Lexeme>& tok) { return tok.lexeme == Lexeme::WORD && tok.value.length() > 10; }, token_t<Lexeme>(Lexeme::WORD, L"Vau!!!"));

	// ## ��������� 2 ������
	if (tokens.size() > 1)
	{
		// �������� ���������� �������� ������ ������
		tokens.erase(unique(tokens.begin(), tokens.end(), [](const token_t<Lexeme>& lhs, const token_t<Lexeme>& rhs) { return lhs.lexeme == Lexeme::SPACE && lhs.lexeme == rhs.lexeme; }), tokens.end());

		//���������� ������� ����� ����� ����������
		Lexeme prevLex, curLex, nextLex;
		for (auto it = tokens.begin(); it != tokens.end() - 1; ++it)
		{
			curLex = (*it).lexeme;
			nextLex = (*(it + 1)).lexeme;

			if (curLex == Lexeme::PUNCT_MARK && nextLex != Lexeme::SPACE)
				it = tokens.insert(it + 1, token_t<Lexeme>(Lexeme::SPACE, L" "));
		}

		// ## ��������� 3 ������
		if (tokens.size() > 2)
		{
			// �������� ������� ����� ������ � ������ ����������
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
		//wif.imbue(locale(wif.getloc(), new codecvt_utf8<wchar_t, UTF8_MAGIC, consume_header>()));
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
		{ Lexeme::WORD,			wregex(L"[a-zA-Z�-��-�]+") },
		{ Lexeme::PUNCT_MARK,	wregex(L"[\\.,!\\?:;]") },
		{ Lexeme::SPACE,		wregex(L" ") },
		{ Lexeme::TABULATION,	wregex(L"\\t") },
		{ Lexeme::NEWLINE,		wregex(L"\\n") },
	};

	FileToString(L"C:\\Users\\PolarHIGH\\Documents\\On Line\\lab2_oop.txt", text);

	wcout << L"[�������� �����]" << endl;
	wcout << text << endl << endl << endl;

	LexParse(text, lexRules, tokens);
	ApplyRules(tokens);
	TokensToString(tokens, text);

	wcout << L"[��������������� �����]" << endl;

	// @TODO ����� �� 40 �������� �� ������

	wcout << text << endl << endl;

	return 0;
}