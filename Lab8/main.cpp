/*
�����:
����: 2015

1. ����������� ���������, �������, ��������� ������ ����������� ��������� � ��������, �������� ������ ������� ������ ����� � ���������  ������ �� ����� PI

2. ����������� ���������, �������:
a. ��������� �������� �������������� ����� ��������� ��:
	i. ����� Shape.
		1. �������� ���������� � ��������� ������ ������ (���������� x � y).
		2. �������� ����� IsMoreLeft, ����������� ���������� ����������� �� ������ ������ ����� (������������ �� ��������� ������) ��� ������ ���������� � �������� ���������
		3. �������� ����� IsUpper, ����������� ���������� ����������� �� ������ ������ ���� (������������ �� ��������� ������) ��� ������ ���������� � �������� ���������
		4. ���������� ����� ����������� ������� ��������� Draw (������ ������ � ���������� ���� ������ ������ �������� �� ����������� ����� ���� �������� � ��������� �����)
	ii. ����� Circle ����������� �� ������ Shape
		1. ��������� Draw
	iii. ����� Triangle ����������� �� ������ Shape
		1. ��������� Draw
	iv. ����� Square ����������� �� ������ Shape
		1. ��������� Draw

b. �������� ������ list<Shape*>, ���������� ����������� �� ��������� ������
c. � ������� ����������� ���������� � ��������� ������� (Draw) ��� ������
d. � ������� ����������� ���������� � ��������� ��������� ������ �� ��������� ������ �����-�������
   (������ � ����, ��� � ������ ������ ������ ���� ������ ����������� �����, ���������� x ) � ������� ������ (Draw)
e. � ������� ����������� ���������� � ��������� ��������� ������ �� ��������� ������ ������-������ � ������� ������
f. � ������� ����������� ���������� � ��������� ��������� ������ �� ��������� ������ ������-���� � ������� ������
g. � ������� ����������� ���������� � ��������� ��������� ������ �� ��������� ������ �����-����� � ������� ������
*/

#define _USE_MATH_DEFINES
#include <cmath>
#include <memory>
#include <list>
#include <algorithm>
#include <functional>


#include "Square.h"
#include "Triangle.h"
#include "Circle.h"
#include "../Lab1/container_utils.h"

using namespace std;

struct IsMoreLeftPred : public binary_function<shared_ptr<Shape>, shared_ptr<Shape>, bool>
{
	bool operator()(const shared_ptr<Shape>& l, const shared_ptr<Shape>& r) const
	{
		return l->IsMoreLeft(*r);
	}
};

struct IsUpperPred : public binary_function<shared_ptr<Shape>, shared_ptr<Shape>, bool>
{
	bool operator()(const shared_ptr<Shape>& l, const shared_ptr<Shape>& r) const
	{
		return l->IsUpper(*r);
	}
};

void DrawShapes(const list<shared_ptr<Shape>>& list)
{
	for_each(list.begin(), list.end(), mem_fn(&Shape::Draw));
}

int main()
{
	// ������� 1
	list<double> doublesList;
	FillContainer(doublesList, 20, -10.0, 10.0);

	transform(doublesList.begin(), doublesList.end(), doublesList.begin(), bind1st(multiplies<double>(), M_PI));

	// ������� 2
	list<shared_ptr<Shape>> shapesList;
	shapesList.push_back(make_shared<Circle>(0, 4));
	shapesList.push_back(make_shared<Square>(2, 5));
	shapesList.push_back(make_shared<Triangle>(-4, 2));
	shapesList.push_back(make_shared<Triangle>(-3, -1));

	cout << "\t[Master list]" << endl;
	DrawShapes(shapesList);
	cout << endl;

	shapesList.sort(IsMoreLeftPred());

	cout << "\t[Sorted left -> right]" << endl;
	DrawShapes(shapesList);
	cout << endl;

	shapesList.sort(binary_negate<IsMoreLeftPred>(IsMoreLeftPred()));

	cout << "\t[Sorted right -> left]" << endl;
	DrawShapes(shapesList);
	cout << endl;

	shapesList.sort(IsUpperPred());

	cout << "\t[Sorted up -> down]" << endl;
	DrawShapes(shapesList);
	cout << endl;

	shapesList.sort(binary_negate<IsUpperPred>(IsUpperPred()));

	cout << "\t[Sorted down -> up]" << endl;
	DrawShapes(shapesList);
	cout << endl;

	return 0;
}