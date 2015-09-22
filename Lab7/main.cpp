/*
�����:
����: 2015

���������� ��������� ��������� �������:

1. ����������� �������,  ����������� �������� ���������� � ������������������ ����� ����� (������ ����� ��������� ����� �� -500 �� 500).
   ������� ����� ��������� ������������������ ���������� for_each ������ ������������� ��������� ����������:
	a. ������������ ����� � ������������������
	b. ����������� ����� � ������������������
	c. ������� ����� � ������������������
	d. ���������� ������������� �����
	e. ���������� ������������� �����
	f. ����� �������� ��������� ������������������
	g. ����� ������ ��������� ������������������
	h. ��������� �� ������ � ��������� �������� ������������������.

��������� ������ ��������� �� �������� ��������������� �������������������.
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