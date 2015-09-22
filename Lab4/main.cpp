/* Автор: 
Дата: 2015

Напишите программу – «телефонную книжку».
Записи(имя и телефон) должны хранится в каком - либо STL - контейнере(vector или list), причем крайне желательно, чтобы от типа контейнера не зависело ничего,
кроме одной строки в программе – объявления этого контейнера(указание: используйте typedef).

Программа должна поддерживать следующие операции :
1) Просмотр текущей записи
2) Переход к следующей записи
3) Переход к предыдущей записи
4) Вставка записи перед / после просматриваемой
5) Замена просматриваемой записи
6) Вставка записи в конец базы данных
7) Переход вперед / назад через n записей.*/

#include <iostream>
#include <memory>
#include <locale>
#include <map>
#include <functional>
#include "Phonebook.h"
#include <Windows.h>

using namespace std;

enum class CMD
{
	CURRENT,
	NEXT,
	PREVIOUS,
	MOVE,
	INSERT_AFTER,
	INSERT_BEFORE,
	INSERT_END,
	REPLACE,
};

void Gotoxy(short x, short y)
{
	COORD pos = { x, y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}

void CursorStore(bool store, COORD& pos)
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

	if (store)
	{
		CONSOLE_SCREEN_BUFFER_INFO bufInfo;
		GetConsoleScreenBufferInfo(output, &bufInfo);

		pos = bufInfo.dwCursorPosition;
	}
	else
	{
		Gotoxy(pos.X, pos.Y);
	}
}

void DrawList(const Phonebook& phoneBook, short x, short y)
{
	COORD pos;
	CursorStore(true, pos);

	short ydef = y;

	//clear
	y = ydef;
	for (const auto& rec : phoneBook)
	{
		Gotoxy(x - 1, y++);
		wcout << L"\t\t\t\t\t\t"; // dirt
	}

	// fill
	y = ydef;
	for (const auto& rec : phoneBook)
	{
		if (rec == phoneBook.Current())
		{
			Gotoxy(x - 1, y);
			wcout << L">";
		}

		Gotoxy(x, y++);
		wcout << *rec << endl;
	}

	CursorStore(false, pos);
}

void DrawHelp(short x, short y)
{
	COORD pos;
	CursorStore(true, pos);

	const wchar_t lines[][50] =
	{
		{ L"1 - next" },
		{ L"2 - previus" },
		{ L"3 - move" },
		{ L"4 - insert after | inpt: name, phone" },
		{ L"5 - insert before | inpt: name, phone" },
		{ L"6 - insert end | inpt: name, phone" },
		{ L"7 - replace | inpt: name, phone" }
	};

	for (const auto str : lines)
	{
		Gotoxy(x, y++);
		wcout << str;
	}

	CursorStore(false, pos);
}

void CmdsHandler(Phonebook& pb, CMD cmd)
{
	wstring name, phone;
	function<void(Phonebook&, const std::shared_ptr<Record>&)> callFunc = nullptr;

	switch (cmd)
	{
	case CMD::CURRENT:
		if (!pb.IsEmpty())
			pb.Current();
		break;

	case CMD::NEXT:
		if (pb.HasNext())
			pb.MoveNext();
		break;

	case CMD::PREVIOUS:
		if (pb.HasPrevious())
			pb.MovePrevious();
		break;

	case CMD::MOVE:
	{
		int movPos;
		cin >> movPos;
		pb.Move(movPos);
	}
	break;

	case CMD::INSERT_AFTER:
		callFunc = &Phonebook::InsertAfter;
		break;

	case CMD::INSERT_BEFORE:
		callFunc = &Phonebook::InsertBefore;
		break;

	case CMD::INSERT_END:
		callFunc = &Phonebook::InsertLast;
		break;

	case CMD::REPLACE:
		callFunc = &Phonebook::ReplaceCurrent;
		break;

	default:
		wcout << L"Unknown cmd" << endl;
		break;
	}

	if (callFunc != nullptr)
	{
		wcin >> name >> phone;
		callFunc(pb, make_shared<Record>(name, phone));
	}
}

int main()
{
	Phonebook pbook;
	pbook.InsertLast(make_shared<Record>(L"Ivanov", L"123-45-12"));
	pbook.InsertLast(make_shared<Record>(L"Petrov", L"345-12-42"));
	pbook.InsertLast(make_shared<Record>(L"Sergeev", L"111-00-33"));

	DrawHelp(40, 0);

	int cmd;
	do
	{
		DrawList(pbook, 40, 10);
		wcin >> cmd;
		CmdsHandler(pbook, static_cast<CMD>(cmd));
	} while (true);

	return 0;
}