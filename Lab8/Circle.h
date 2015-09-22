#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "Shape.h"

class Circle :
	public Shape
{
public:
	Circle(int x, int y) : Shape(x, y) { }
	~Circle() { }

	virtual void Draw() const override
	{
		std::cout << "Circle(" << m_Center.x << ", " << m_Center.y << ")" << std::endl;
	}
};

#endif // _CIRCLE_H_