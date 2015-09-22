/* �����: 
����: 2015

1. �������� ���������, ������� ��������� ��������� ��������:
a. ������ ���������� ���������� �����
b. �������� �����, ������ ��������� ������������������ �������� ����������� ��������� �/��� ������� ��������� �/��� ��������� ����� ������
c. ������� ������ ���� �������������� � ������ ��� ���������� (������� � ����, ��� ���� � �� �� ����� ����� �������������� � ������ ������ ���� ���)


2. �������� ���������, ������� ��������� ��������� �������� (��� �������� ������ ����������� � ������� ����������� ����������):
a. ��������� ������ ��������������� ��������. �������������� ������ ����� ���� �������������, ���������, ��������������� ��� ���� ����������.
b. ������������ ����� ���������� ������ ���� ����� ������������ � ������� (��� ����������� ��������� � ������ ����� 3, ������� 4 � �.�.)
c. ������������ ���������� �������������, ��������� � ��������������� � �������
d. ������� ��� �������������
e. �� ��������� ����� ������� ������� vector<Point>, ������� �������� ���������� ����� �� ������ (�����) ������ ������, �.�.
   ������ ������� ����� ������� �������� ���������� ����� �� ������� ������ ������, ������ ������� ����� ������� �������� ���������� ����� �� ������� ������ ������ � �.�.
f. �������� ������ ���, ����� �� �������� � ������ ��� ������������, ����� ��� ��������, � ����� ��������������.
g. ������������� ������ ����� ������� ����� ������
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
	bool squareFlag; // true ���� � ������ ��� ���� ������

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
	// a) TODO ���������� ������� ��������
	shapes.emplace_back(vector<Point>({ Point(0, 0), Point(0, 4), Point(6, 4), Point(6, 0) }), true);
	shapes.emplace_back(vector<Point>({ Point(0, 0), Point(0, 4), Point(4, 4), Point(4, 0) }), true);
	shapes.emplace_back(vector<Point>({ Point(0, 0), Point(0, 4), Point(4, 6), Point(0, 6), Point(12, -12) }));

	// b) ����� ���-�� ������
	int totalVertexes = accumulate(shapes.begin(), shapes.end(), 0, [](int sumFar, const Shape& shape) { return sumFar + shape.GetVertexNum(); });

	// c) ���-�� �������������, ��������� � ���������������
	int squares = count_if(shapes.begin(), shapes.end(), IsSquareFunct());
	int triangles = count_if(shapes.begin(), shapes.end(), IsTriFunct());
	int rectangles = count_if(shapes.begin(), shapes.end(), IsRectFunct());

	// d) �������� ���� ��������������
	shapes.erase(remove_if(shapes.begin(), shapes.end(), [](const Shape& shape) { return shape.GetVertexNum() == 5; }), shapes.end());

	// e) ������ � ������� �� ������� �� ������ ������ �� shapes
	vector<Point> points(shapes.size());
	transform(shapes.begin(), shapes.end(), points.begin(), [](const Shape& shape) { return shape.vertexes[rand() % shape.GetVertexNum()]; });

	// f) ����������: ������������, ��������, ��������������
	//partition()
}

void Task1()
{
	// a) ������ �����
	string file;
	ReadFile("text.txt", file);

	// b) ��������� ����
	istringstream iss(file);
	vector<string> words;
	copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(words));

	// c) �������� ����������
	sort(words.begin(), words.end());
	words.erase(unique(words.begin(), words.end()), words.end());

	// �����
	copy(words.begin(), words.end(), ostream_iterator<string>(cout, "\n"));
}

int main()
{
	Task1();
	Task2();

	return 0;
}