/*
Автор:
Дата: 2015

Необходимо выполнить ВСЕ задания.

1. Ниже приведен интерфейс класса очереди с приоритетами, который функционирует следующим образом.
 - В очередь могут быть добавлены элементы, каждому элементу при добавлении присваивается один из трех уровней приоритета(low, normal, high)
 - Элементы из очереди извлекаются в соответствии с их приоритетами(сначала извлекаются элементы с приоритетом high, потом normal, потом low),
   элементы с одинаковыми приоритетами извлекаются из очереди в порядки их поступления.
 - В очереди также может происходить операция акселерации – все элементы с приоритетом low находящиеся в момент акселерации в очереди увеличивают
   свой приоритет до high и «обгоняют» элементы с приоритетом normal.


2. Разработайте программу, которая
 - Заполняет list<int> 15 случайными значениями от 1 до 20, список может содержать от 0 до 20 значений(обязательно проверить на длине списка 0, 1. 2, 3, 4, 5, 7, 14)
 - Выводит содержимое списка в следующем порядке : первый элемент, последний элемент, второй элемент, предпоследний элемент, тритий элемент и т.д.

Например если список содержит :
1 2 3 4 5 6 7 8
то вывод будет иметь вид
1 8 2 7 3 6 4 5

Подсказка : можно использовать рекурсию и двунаправленные итераторы */

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