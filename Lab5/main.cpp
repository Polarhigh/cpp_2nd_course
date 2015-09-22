/*
�����:
����: 2015

1. �������� ���������, ������� ��������� ��������� ��������:
 - ��������� vector<DataStruct> ����������� DataStruct, ��� ���� key1 � key2, ������������ ��������� ������� � ��������� �� -5 �� 5, str ����������� �� ������� (������� �������� 10 ������������ �����, ������ ������ ������������ ��������� �������)
 - ������� ���������� ������ �� ������
 - ��������� ������ ��������� �������:
  * �� ����������� key1
  * ���� key1 ����������, �� �� ����������� key2
  * ���� key1 � key2 ����������, �� �� ����������� ������ ������ str
 - ������� ���������� ������ �� ������
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "../Lab1/container_utils.h"

using namespace std::chrono;
using namespace std;

struct DataStruct
{
	int key1;
	int key2;
	string str;

	DataStruct() {}

	DataStruct(int key1, int key2, const string& str)
	{
		this->key1 = key1;
		this->key2 = key2;
		this->str = str;
	}

	friend ostream& operator<<(ostream& os, const DataStruct& ds);
};

ostream& operator<<(ostream& os, const DataStruct& ds)
{
	os << ds.key1 << " \t " << ds.key2 << " \t " << ds.str;
	return os;
}

const char g_Strings[][20] =
{
	{ "string 1 --" },
	{ "string 2" },
	{ "string 3 dadasda" },
	{ "string 4as9asff9" },
	{ "string 5ff" },
	{ "string 6fafadf" },
	{ "string 7aa3" },
	{ "string 8a" },
	{ "string 9" },
	{ "string 10" },
	{ "string 11oooooooopp" },
};

void FillVector(vector<DataStruct>& vec, int count = 10)
{
	unsigned seed = static_cast<unsigned>(system_clock::now().time_since_epoch().count());

	mt19937 gen(seed);

	uniform_int_distribution<int> distrKeys(-5, 5);
	uniform_int_distribution<int> distrStr(0, 10);

	for (int i = 0; i < count; ++i)
		vec.push_back(
			DataStruct(distrKeys(gen), distrKeys(gen), g_Strings[distrStr(gen)])
			);
}

void SortVector(vector<DataStruct>& vec)
{
	sort(vec.begin(), vec.end(), [](const DataStruct& i, const DataStruct& j)
	{
		if (i.key1 == j.key1)
		{
			if (i.key2 == j.key2)
			{
				return i.str.length() < j.str.length();
			}

			return i.key2 < j.key2;
		}

		return i.key1 < j.key1;
	});
}

int main()
{
	vector<DataStruct> vec;
	FillVector(vec);
	PrintContainer(vec);
	cout << endl << endl;

	SortVector(vec);

	PrintContainer(vec);
	cout << endl << endl;

	return 0;
}