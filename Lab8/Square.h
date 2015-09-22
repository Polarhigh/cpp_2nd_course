#ifndef _SQUARE_H_
#define _SQUARE_H_

#include "Shape.h"

class Square :
	public Shape
{
public:
	Square(int x, int y) : Shape(x, y) { }
	~Square() { }

	virtual void Draw() const override
	{
		std::cout << "Square(" << m_Center.x << ", " << m_Center.y << ")" << std::endl;
	}
};


#endif // _SQUARE_H_