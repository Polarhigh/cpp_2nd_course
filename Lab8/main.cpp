/*
Автор:
Дата: 2015

1. Разработать программу, которая, используя только стандартные алгоритмы и функторы, умножает каждый элемент списка чисел с плавающей  точкой на число PI

2. Разработать программу, которая:
a. Реализует иерархию геометрических фигур состоящую из:
	i. Класс Shape.
		1. Содержит информацию о положении центра фигуры (координаты x и y).
		2. Содердит метод IsMoreLeft, позволяющий определить расположена ли данная фигура левее (определяется по положению центра) чем фигура переданная в качестве аргумента
		3. Содердит метод IsUpper, позволяющий определить расположена ли данная фигура выше (определяется по положению центра) чем фигура переданная в качестве аргумента
		4. Определяет чисто виртаульную функцию рисования Draw (каждая фигура в реализации этой функци должна выводить на стандартный вывод свое название и положение цента)
	ii. Класс Circle производный от класса Shape
		1. Реализует Draw
	iii. Класс Triangle производный от класса Shape
		1. Реализует Draw
	iv. Класс Square производный от класса Shape
		1. Реализует Draw

b. Содержит список list<Shape*>, заполенный указателями на различные фигуры
c. С помощью стандартных алгоритмов и адаптеров выводит (Draw) все фигуры
d. С помощью стандартных алгоритмов и адаптеров сортирует список по положению центра слева-направо
   (имется в виду, что в начале списка должны идти фигуры находящиеся левее, координата x ) и выводит фигуры (Draw)
e. С помощью стандартных алгоритмов и адаптеров сортирует список по положению центра справа-налево и выводит фигуры
f. С помощью стандартных алгоритмов и адаптеров сортирует список по положению центра сверху-вниз и выводит фигуры
g. С помощью стандартных алгоритмов и адаптеров сортирует список по положению центра снизу-вверх и выводит фигуры
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
	// Задание 1
	list<double> doublesList;
	FillContainer(doublesList, 20, -10.0, 10.0);

	transform(doublesList.begin(), doublesList.end(), doublesList.begin(), bind1st(multiplies<double>(), M_PI));

	// Задание 2
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