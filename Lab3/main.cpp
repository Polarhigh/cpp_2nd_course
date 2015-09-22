#include <iostream>
#include <chrono>
#include <random>
#include <list>
#include <functional>
#include "QueueWithPriority.h"
#include "../Lab1/container_utils.h"

using namespace std;

enum class Priority { HIGH, NORMAL, LOW, _count };

ostream& operator<<(ostream& os, const Priority& p)
{
	switch (p)
	{
	case Priority::HIGH:
		os << "HIGH";
		break;

	case Priority::NORMAL:
		os << "NORMAL";
		break;

	case Priority::LOW:
		os << "LOW";
		break;
	}
	return os;
}

// специальный вывод контейнера (первый элемент, последний элемент, второй элемент, предпоследний элемент, третий элемент и т.д.)
// ЗЫ: омг, как это вообще получилось так сложно сделать T_T
template<class T>
void PrintContainerSpecial(T& cont, const char* delimiter = "\r\n")
{
	typename typedef T::iterator TIterator;
	typename typedef T::reverse_iterator TReverseIterator;
	typename typedef function<void(TIterator, TReverseIterator, size_t)> FuncPrint;

	size_t listSize = cont.size();

	FuncPrint funcPrint = [&](TIterator fwd, TReverseIterator inv, size_t n)
	{
		if (n > listSize)
			return;

		std::cout << (n % 2 == 0 ? *(inv++) : *(fwd++)) << delimiter;
		funcPrint(fwd, inv, ++n);

	};

	funcPrint(cont.begin(), cont.rbegin(), 1);
};

int main()
{
	cout << "[Task 1]";

	QueueWithPriority<int, Priority> q;

	q.PutElementToQueue(0, Priority::HIGH);
	q.PutElementToQueue(3, Priority::LOW);
	q.PutElementToQueue(20, Priority::LOW);
	q.PutElementToQueue(5, Priority::HIGH);
	q.PutElementToQueue(10, Priority::NORMAL);
	q.PutElementToQueue(100, Priority::HIGH);
	q.PutElementToQueue(200, Priority::HIGH);

	q.ToStdOut();

	cout << endl << "[Accelerate...]" << endl;
	q.Accelerate();

	q.ToStdOut();

	cout << endl << "[GetElementFromQueue()]" << endl;
	while (!q.IsEmpty())
		cout << q.GetElementFromQueue() << endl;

	cout << endl << "[Task 2]" << endl;

	// задание 2
	const int LIST_SIZE = 7;

	typedef list<int>::iterator ListIntIter;
	typedef list<int>::reverse_iterator ListIntReverseIter;
	typedef function<void(ListIntIter, ListIntReverseIter, size_t)> FuncSpecialPrint;

	list<int> intList(LIST_SIZE);
	FillContainer(intList, LIST_SIZE, 1, 20);
	PrintContainer(intList, " ");

	cout << endl;
	PrintContainerSpecial(intList, " ");
	cout << endl;

	return 0;
}