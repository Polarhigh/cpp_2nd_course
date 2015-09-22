#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <iostream>

template<class T>
struct Coord
{
    T x;
    T y;

    Coord() { }

    Coord(T x, T y)
    {
        this->x = x;
        this->y = y;
    }
};

class Shape
{
public:
    Shape(int x, int y) : m_Center(x, y) { }
    virtual ~Shape() { }

    bool IsMoreLeft(const Shape& shape) const
    {
        return m_Center.x < shape.m_Center.x;
    }

    bool IsUpper(const Shape& shape) const
    {
        return m_Center.y > shape.m_Center.y;
    }

    virtual void Draw() const = 0;

protected:
    Coord<int> m_Center;
};

#endif // _SHAPE_H_