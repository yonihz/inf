#include <iostream>
#include <list>

#include "shape.hpp"

namespace ilrd
{

Shape::Shape(const Point& pos_, double angle_, COLORS color_, const Point& center_)
    : m_position(pos_), m_angle(angle_), m_color(color_), m_center(center_)
{
}

Shape::~Shape()
{
}

void Shape::SetPos(const Point& pos_)
{
    m_position = pos_;
}

const Point& Shape::GetPos() const
{
    return m_position;
}

void Shape::SetAngle(double angle_)
{
    m_angle = angle_;
}

double Shape::GetAngle() const
{
    return m_angle;
}

void Shape::SetColor(COLORS color_)
{
    m_color = color_;
}

COLORS Shape::GetColor() const
{
    return m_color;
}

void Shape::Revolve(const Point& pivot_, double angle_)
{
    m_center.Revolve(pivot_, angle_);
}

Circle::Circle(int radius_, const Point& pos_, double angle_, COLORS color_)
    : Shape(pos_, angle_, color_), m_radius(radius_)
{

}

Circle::~Circle()
{

}

void Circle::SetRadius(int radius_)
{
    m_radius = radius_;
}

int Circle::GetRadius() const
{
    return m_radius;
}

void Circle::Draw()
{
    std::cout << "Draw circle" << std::endl;
}

Rectangle::Rectangle(int width_, int height_, const Point& pos_, double angle_, COLORS color_)
    : Shape(pos_, angle_, color_), m_height(height_), m_width(width_)
{

}

Rectangle::~Rectangle()
{

}

void Rectangle::SetWidth(int width_)
{
    m_width = width_;
}

int Rectangle::GetWidth() const
{
    return m_width;
}

void Rectangle::SetHeight(int height_)
{
    m_height = height_;
}

int Rectangle::GetHeight() const
{
    return m_height;
}

void Rectangle::Draw()
{
    std::cout << "Draw rectangle" << std::endl;    
}

Square::Square(int side_, const Point& pos_, double angle_, COLORS color_)
    : Shape(pos_, angle_, color_), m_side(side_)
{

}

Square::~Square()
{

}

void Square::SetSide(int side_)
{
    m_side = side_;
}

int Square::GetSide() const
{
    return m_side;
}

void Square::Draw()
{
    std::cout << "Draw square" << std::endl;  
}


Line::Line(int length_, const Point& pos_, double angle_, COLORS color_)
    : Shape(pos_, angle_, color_), m_length(length_)
{

}

Line::~Line()
{

}

void Line::SetLength(int length_)
{
    m_length = length_;
}

int Line::GetLength() const
{
    return m_length;
}

void Line::Draw()
{
    std::cout << "Draw line" << std::endl;     
}


ShapeGroup::ShapeGroup()
    : Shape(Point(), 0, COLOR_RED), m_arr(std::list<Shape*>())  
{
}

ShapeGroup::~ShapeGroup()
{
}

void ShapeGroup::Draw()
{

}

void ShapeGroup::Add(Shape* to_add_)
{

}

void ShapeGroup::Remove(Shape* to_remove_)
{

}

void ShapeGroup::SetPos(const Point& pos_)
{

}

void ShapeGroup::SetAngle(double angle_)
{

}

void ShapeGroup::SetColor(COLORS color_)
{

}

size_t ShapeGroup::GetGroupSize()
{

}


} //namespace ilrd