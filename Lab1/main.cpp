/*
�����: ;
����: 2015
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "container_utils.h"
#include "bubble_sort.h"
#include "time_utils.h"

using namespace std;

/* ������� 6
�������� ������� void fillRandom(double* array, int size) ����������� ������ ���������� ���������� � ��������� �� - 1.0 �� 1.0.
��������� � ������� �������� ������� ������� �������� 5, 10, 25, 50, 100 � ������������ ��� ����������
(� ������� ������ �������������� ����� ��������� ����������������� ��� ���������� �������������� �����)
*/
void Task6()
{
	const int sizes[] = { 5, 10, 25, 50, 100 };
	const int count = sizeof(sizes) / sizeof(int);

	vector<vector<double>> vectors(count);

	for (int i = 0; i < count; ++i)
	{
		FillContainer(vectors[i], sizes[i], -1.0, 1.0);
		VectorBubbleSort3(vectors[i]);
		PrintContainer(vectors[i], " ");
		cout << endl;
	}
}

/* ������� 5
�������� ���������, ����������� � ������� �����, ���������� �� ������������ ����� (���������� ����� �������� ����� 0).
������� ��� ��������, ������� ������� �� 2 (�� ����������� ����������� ��������� STL), ���� ��������� ����� 1.
���� ��������� ����� 2, �������� ����� ������� ����� ������� ������� �� 3 ��� �������.
*/
void Task5()
{
	int in;
	vector<int> inVec;

	// ����
	cout << "Enter digit" << endl;
	do
	{
		cin >> in;

		if (in == 0)
			break;

		inVec.push_back(in);
	} while (true);

	cout << "input vec:" << endl;
	PrintContainer(inVec, ", ");

	// ������� ������� ���� ������� �� 2
	if (inVec.back() == 1)
	{
		inVec.erase(remove_if(inVec.begin(), inVec.end(), [](int a) { return a % 2 == 0; }), inVec.end());
	}
	// �������� 3 ������� ����� ��������, ������� ������� �� 3
	else if (inVec.back() == 2)
	{
		for (auto it = inVec.begin(); it != inVec.end();)
		{
			if (*it % 3 == 0)
			{
				it = inVec.insert(it + 1, { 1, 1, 1 });
				it += 3;
			}
			else
				++it;
		}
	}

	cout << "processed vec:" << endl;
	PrintContainer(inVec, " ");
}

/* ������� 4
���������� �� ���������� ������ � ���������� ���������� �����, ���������� ������ � ������ ����� ������� ���� (��� ������ � ���������� STL)
*/
void Task4()
{
	const int FILE_BUFF_SIZE = 200;

	fstream fs;

	fs.open("C:\\Users\\PolarHIGH\\Documents\\On Line\\.htaccess", fstream::in);
	if (fs.is_open())
	{
		char buf[FILE_BUFF_SIZE];
		vector<char> vecBuf;

		fs.get(buf, sizeof(buf) / sizeof(char), '\r'); // upd: ����� \r
		fs.close();

		vecBuf.assign(begin(buf), end(buf)); // ����� ����������� ����� ������� ����

		for (auto it = vecBuf.begin(); it != vecBuf.end(), *it != '\0'; ++it)
			cout << *it;
		cout << endl;
	}
	else
	{
		cout << "Can't open file" << endl;
	}
}


/* ������� 1-3
���������� � �������������� ������ ������� ������� � ��������� ������� �������� [], ����� at(), ��������� (���������) � ���������� std
*/
void VectorSortPerformance()
{
	const int VECTOR_SIZE = 1000;

	long long execTimeMs, execTimeNs;
	vector<int> masterVector, bbl1Vector, bbl2Vector, bbl3Vector, ssVector;

	FillContainer(masterVector, VECTOR_SIZE, -100, 100);
	bbl1Vector = masterVector;
	bbl2Vector = masterVector;
	bbl3Vector = masterVector;
	ssVector = masterVector;

	GetExecutionTime([&]() mutable { VectorBubbleSort(bbl1Vector); }, execTimeMs, execTimeNs);
	PrintExecutionTime("bubble sort, operator []: ", execTimeMs, execTimeNs);

	GetExecutionTime([&]() mutable { VectorBubbleSort2(bbl2Vector); }, execTimeMs, execTimeNs);
	PrintExecutionTime("bubble sort, method at(): ", execTimeMs, execTimeNs);

	GetExecutionTime([&]() mutable { VectorBubbleSort3(bbl3Vector); }, execTimeMs, execTimeNs);
	PrintExecutionTime("bubble sort, iterators: ", execTimeMs, execTimeNs);

	GetExecutionTime([&]() mutable { sort(ssVector.begin(), ssVector.end()); }, execTimeMs, execTimeNs);
	PrintExecutionTime("std sort: ", execTimeMs, execTimeNs);
}

int main()
{
	cout << "[Task 1-3]" << endl;
	VectorSortPerformance();

	cout << endl << "[Task 4]" << endl;
	Task4();

	cout << endl << "[Task 5]" << endl;
	Task5();

	cout << endl << "[Task 6]" << endl;
	Task6();

	return 0;
}