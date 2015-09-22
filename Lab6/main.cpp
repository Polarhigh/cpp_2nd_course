/* Автор: 
Дата: 2015

1. Написать программу, которая выполняет следующие действия:
a. Читает содержимое текстового файла
b. Выделяет слова, словом считаются последовательность символов разделенных пробелами и/или знаками табуляции и/или символами новой строки
c. Вывести список слов присутствующий в тексте без повторений (имеется в виду, что одно и то же слово может присутствовать в списке только один раз)


2. Написать программу, которая выполняет следующие действия (все операции должны выполняться с помощью стандартных алгоритмов):
a. Заполняет вектор геометрическими фигурами. Геометрическая фигура может быть треугольником, квадратом, прямоугольником или пяти угольником.
b. Подсчитывает общее количество вершин всех фигур содержащихся в векторе (так треугольник добавляет к общему числу 3, квадрат 4 и т.д.)
c. Подсчитывает количество треугольников, квадратов и прямоугольников в векторе
d. Удаляет все пятиугольники
e. На основании этого вектора создает vector<Point>, который содержит координаты одной из вершин (любой) каждой фигуры, т.е.
   первый элемент этого вектора содержит координаты одной из вершину первой фигуры, второй элемент этого вектора содержит координаты одной из вершину второй фигуры и т.д.
f. Изменяет вектор так, чтобы он содержал в начале все треугольники, потом все квадраты, а потом прямоугольники.
g. Распечатывает вектор после каждого этапа работы
*/

#include <sstream>
#include <fstream>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

struct Point
{
	int x;
	int y;

	Point() {}

	Point(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
};

struct Shape
{
	vector<Point> vertexes;
	bool squareFlag; // true если у фигуры все углы прямые

	Shape() {}

	Shape(vector<Point>& vertexes, bool square = false) : vertexes(vertexes), squareFlag(square) { }

	inline int GetVertexNum() const
	{
		return static_cast<int>(vertexes.size());
	}
};

struct IsSquareFunct : public unary_function<Shape, bool>
{
	bool operator()(const Shape& shape) const
	{
		if (shape.squareFlag)
		{
			if (abs(shape.vertexes[0].x - shape.vertexes[3].x) == abs(shape.vertexes[0].y - shape.vertexes[1].y))
				return true;
		}

		return false;
	}
};

struct IsRectFunct : public unary_function<Shape, bool>
{
	bool operator()(const Shape& shape) const
	{
		return shape.squareFlag;
	}
};

struct IsTriFunct : public unary_function<Shape, bool>
{
	bool operator()(const Shape& shape) const
	{
		return shape.GetVertexNum() == 3;
	}
};


void ReadFile(const char* file, string& outString)
{
	fstream in(file, fstream::in);

	if (in)
	{
		ostringstream content;
		content << in.rdbuf();
		in.close();

		outString = content.str();
	}
}

void Task2()
{
	vector<Shape> shapes;
	// a) TODO заполнение вектора рандомом
	shapes.emplace_back(vector<Point>({ Point(0, 0), Point(0, 4), Point(6, 4), Point(6, 0) }), true);
	shapes.emplace_back(vector<Point>({ Point(0, 0), Point(0, 4), Point(4, 4), Point(4, 0) }), true);
	shapes.emplace_back(vector<Point>({ Point(0, 0), Point(0, 4), Point(4, 6), Point(0, 6), Point(12, -12) }));

	// b) общее кол-во вершин
	int totalVertexes = accumulate(shapes.begin(), shapes.end(), 0, [](int sumFar, const Shape& shape) { return sumFar + shape.GetVertexNum(); });

	// c) кол-во треугольников, квадратов и прямоугольников
	int squares = count_if(shapes.begin(), shapes.end(), IsSquareFunct());
	int triangles = count_if(shapes.begin(), shapes.end(), IsTriFunct());
	int rectangles = count_if(shapes.begin(), shapes.end(), IsRectFunct());

	// d) удаление всех пятиугольников
	shapes.erase(remove_if(shapes.begin(), shapes.end(), [](const Shape& shape) { return shape.GetVertexNum() == 5; }), shapes.end());

	// e) вектор в котором по вершине из каждой фигуры из shapes
	vector<Point> points(shapes.size());
	transform(shapes.begin(), shapes.end(), points.begin(), [](const Shape& shape) { return shape.vertexes[rand() % shape.GetVertexNum()]; });

	// f) сортировка: треугольники, квадраты, прямоугольники
	//partition()
}

void Task1()
{
	// a) чтение файла
	string file;
	ReadFile("text.txt", file);

	// b) выделение слов
	istringstream iss(file);
	vector<string> words;
	copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(words));

	// c) удаление повторений
	sort(words.begin(), words.end());
	words.erase(unique(words.begin(), words.end()), words.end());

	// вывод
	copy(words.begin(), words.end(), ostream_iterator<string>(cout, "\n"));
}

int main()
{
	Task1();
	Task2();

	return 0;
}