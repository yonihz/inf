#include <iostream>
#include <list>

#include "shape.hpp"

namespace ilrd
{

Shape::Shape(const Point& pos_, double angle_, COLORS color_)
    : m_position(pos_), m_angle(angle_), m_color(color_)
{
}

Shape::~Shape()
{
}

void Shape::SetPos(const Point& pos_)
{
    m_position.Move(pos_.GetX(), pos_.GetY());
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
    Point end(m_position);
    SetPos(end.Revolve(pivot_, angle_));
    SetAngle(GetAngle() + angle_);
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
    DrawCircle(m_color, (int)m_position.GetX(), (int)m_position.GetY(), m_radius);
}

Rectangle::Rectangle(int width_, int height_, const Point& pos_, double angle_, COLORS color_)
    : Shape(pos_, angle_, color_), m_width(width_), m_height(height_)
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
    Point p1, p2, p3, p4;

    p1.Move(m_position.GetX() - (m_width/2), m_position.GetY() + (m_height/2));
    p2.Move(m_position.GetX() + (m_width/2), m_position.GetY() + (m_height/2));
    p3.Move(m_position.GetX() + (m_width/2), m_position.GetY() - (m_height/2));
    p4.Move(m_position.GetX() - (m_width/2), m_position.GetY() - (m_height/2));

    p1.Revolve(m_position, m_angle);
    p2.Revolve(m_position, m_angle);
    p3.Revolve(m_position, m_angle);
    p4.Revolve(m_position, m_angle);

    DrawPolygon(
        m_color,
        4,
        (int)p1.GetX(),
        (int)p1.GetY(),
        (int)p2.GetX(),
        (int)p2.GetY(),
        (int)p3.GetX(),
        (int)p3.GetY(),
        (int)p4.GetX(),
        (int)p4.GetY());        
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
    Point p1, p2, p3, p4;

    p1.Move(m_position.GetX() - (m_side/2), m_position.GetY() + (m_side/2));
    p2.Move(m_position.GetX() + (m_side/2), m_position.GetY() + (m_side/2));
    p3.Move(m_position.GetX() + (m_side/2), m_position.GetY() - (m_side/2));
    p4.Move(m_position.GetX() - (m_side/2), m_position.GetY() - (m_side/2));

    p1.Revolve(m_position, m_angle);
    p2.Revolve(m_position, m_angle);
    p3.Revolve(m_position, m_angle);
    p4.Revolve(m_position, m_angle);

    DrawPolygon(
        m_color,
        4,
        (int)p1.GetX(),
        (int)p1.GetY(),
        (int)p2.GetX(),
        (int)p2.GetY(),
        (int)p3.GetX(),
        (int)p3.GetY(),
        (int)p4.GetX(),
        (int)p4.GetY());     
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
    Point p1, p2;

    p1.Move(m_position.GetX() - (m_length/2), m_position.GetY());
    p2.Move(m_position.GetX() + (m_length/2), m_position.GetY());

    p1.Revolve(m_position, m_angle);
    p2.Revolve(m_position, m_angle);

    DrawPolygon(
        m_color,
        2,
        (int)p1.GetX(),
        (int)p1.GetY(),
        (int)p2.GetX(),
        (int)p2.GetY());       
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