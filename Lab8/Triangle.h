#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "Shape.h"

class Triangle :
	public Shape
{
public:
	Triangle(int x, int y) : Shape(x, y) { }
	~Triangle() { }

	virtual void Draw() const override
	{
		std::cout << "Triangle(" << m_Center.x << ", " << m_Center.y << ")" << std::endl;
	}
};

#endif // _TRIANGLE_H_