/*
Автор:
Дата: 2015

Необходимо выполнить следующее задание:

1. Разработать функтор,  позволяющий собирать статистику о последовательности целых чисел (послед может содержать числа от -500 до 500).
   Функтор после обработки последовательности алгоритмом for_each должен предоставлять следующую статистику:
    a. Максимальное число в последовательности
    b. Минимальное число в последовательности
    c. Среднее чисел в последовательности
    d. Количество положительных чисел
    e. Количество отрицательных чисел
    f. Сумму нечетных элементов последовательности
    g. Сумму четных элементов последовательности
    h. Совпадают ли первый и последний элементы последовательности.

Проверить работу программы на случайно сгенерированных последовательностях.
*/

#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>
#include "../Lab1/container_utils.h"

using namespace std;

template<typename T, typename Tavg = double>
struct StatisticsFunct : unary_function<T, void>
{
    T max = T();
    T min = T();
    Tavg avg = Tavg();
    unsigned moreZeroCount = 0;
    unsigned lessZeroCount = 0;
    unsigned oddCount = 0;
    unsigned evenCount = 0;
    T oddSum = T();
    T evenSum = T();

    StatisticsFunct() { }

    void operator()(T val)
    {
        if (val > max) max = val;
        if (val < min) min = val;
        if (val > 0) moreZeroCount++;
        if (val < 0) lessZeroCount++;

        if (val % 2 == 0)
        {
            oddSum += val;
            oddCount++;
        }
        else
        {
            evenSum += val;
            evenCount++;
        }

        avg = static_cast<Tavg>(evenSum + oddSum) / static_cast<Tavg>(evenCount + oddCount);
    }

    friend ostream& operator<<(ostream& os, const StatisticsFunct<T, Tavg>& sf);
};

ostream& operator<<(ostream& os, const StatisticsFunct<int, double>& sf)
{
    os << "min: " << sf.min << endl <<
        "max: " << sf.max << endl <<
        "avg: " << sf.avg << endl <<
        "more zero count: " << sf.moreZeroCount << endl <<
        "less zero count: " << sf.lessZeroCount << endl <<
        "even sum: " << sf.evenSum << endl <<
        "odd sum: " << sf.oddSum << endl;
    return os;
}

int main()
{
    vector<int> intVec;
    FillContainer(intVec, 100, -500, 500);

    StatisticsFunct<int> vecStats = for_each(intVec.begin(), intVec.end(), StatisticsFunct<int>());

    cout << "[Vector]" << endl;
    PrintContainer(intVec, ", ");

    cout << endl << endl << "[Stats]" << endl;
    cout << vecStats;

    return 0;
}