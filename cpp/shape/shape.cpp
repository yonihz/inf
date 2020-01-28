#include <iostream>
#include <list>

#include <boost/lexical_cast.hpp>
#include "shape.hpp"

using boost::lexical_cast;

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
    : Shape(Point(), 0, COLOR_RED), m_list(std::list<Shape*>())  
{
}

ShapeGroup::~ShapeGroup()
{
}

void ShapeGroup::Draw()
{
    std::list<Shape*>::iterator it;

	for (it = m_list.begin(); it != m_list.end(); ++it)
    {
        (*it)->Draw();
    }
}

void ShapeGroup::Add(Shape* to_add_)
{
    m_list.push_back(to_add_);
}

void ShapeGroup::Remove(Shape* to_remove_)
{
    m_list.remove(to_remove_);
}

void ShapeGroup::SetPos(const Point& pos_)
{
    double x_offset = 0, y_offset = 0;
    double x_new = 0, y_new = 0;

    x_offset = pos_.GetX() - m_position.GetX();
    y_offset = pos_.GetY() - m_position.GetY();

    std::list<Shape*>::iterator it;

	for (it = m_list.begin(); it != m_list.end(); ++it)
    {
        x_new = (*it)->GetPos().GetX() + x_offset;
        y_new = (*it)->GetPos().GetY() + y_offset;

        (*it)->SetPos(Point(x_new, y_new));
    }

    m_position = pos_;
}

void ShapeGroup::SetAngle(double angle_)
{
    double x_sum = 0, y_sum = 0;
    size_t list_size = m_list.size();

    std::list<Shape*>::iterator it;

	for (it = m_list.begin(); it != m_list.end(); ++it)
    {
        x_sum += (*it)->GetPos().GetX();
        y_sum += (*it)->GetPos().GetY();
    }

    Point center(x_sum / list_size, y_sum / list_size);

	for (it = m_list.begin(); it != m_list.end(); ++it)
    {
        (*it)->Revolve(center, angle_);
    }
}

void ShapeGroup::SetColor(COLORS color_)
{
    std::list<Shape*>::iterator it;

	for (it = m_list.begin(); it != m_list.end(); ++it)
    {
        (*it)->SetColor(color_);
    }
}

size_t ShapeGroup::GetGroupSize() const
{
    return m_list.size();
}

std::map<std::string, std::string> Circle::ToMap()
{
    std::map<std::string, std::string> m;
    m.insert(std::pair<std::string,std::string>("type", typeid(this).name()));
    m.insert(std::pair<std::string,std::string>("pos_x",lexical_cast<std::string>(GetPos().GetX())));
    m.insert(std::pair<std::string,std::string>("pos_y",lexical_cast<std::string>(GetPos().GetY())));
    m.insert(std::pair<std::string,std::string>("angle",lexical_cast<std::string>(GetAngle())));
    m.insert(std::pair<std::string,std::string>("color",lexical_cast<std::string>(GetColor())));
    m.insert(std::pair<std::string,std::string>("radius",lexical_cast<std::string>(GetRadius())));

    return m;
}

std::map<std::string, std::string> Rectangle::ToMap()
{
    std::map<std::string, std::string> m;
    m.insert(std::pair<std::string,std::string>("type", typeid(this).name()));
    m.insert(std::pair<std::string,std::string>("pos_x",lexical_cast<std::string>(GetPos().GetX())));
    m.insert(std::pair<std::string,std::string>("pos_y",lexical_cast<std::string>(GetPos().GetY())));
    m.insert(std::pair<std::string,std::string>("angle",lexical_cast<std::string>(GetAngle())));
    m.insert(std::pair<std::string,std::string>("color",lexical_cast<std::string>(GetColor())));
    m.insert(std::pair<std::string,std::string>("width",lexical_cast<std::string>(GetWidth())));
    m.insert(std::pair<std::string,std::string>("height",lexical_cast<std::string>(GetHeight())));

    return m;
}

std::map<std::string, std::string> Square::ToMap()
{
    std::map<std::string, std::string> m;
    m.insert(std::pair<std::string,std::string>("type", typeid(this).name()));
    m.insert(std::pair<std::string,std::string>("pos_x",lexical_cast<std::string>(GetPos().GetX())));
    m.insert(std::pair<std::string,std::string>("pos_y",lexical_cast<std::string>(GetPos().GetY())));
    m.insert(std::pair<std::string,std::string>("angle",lexical_cast<std::string>(GetAngle())));
    m.insert(std::pair<std::string,std::string>("color",lexical_cast<std::string>(GetColor())));
    m.insert(std::pair<std::string,std::string>("side",lexical_cast<std::string>(GetSide())));

    return m;
}

std::map<std::string, std::string> Line::ToMap()
{
    std::map<std::string, std::string> m;
    m.insert(std::pair<std::string,std::string>("type", typeid(this).name()));
    m.insert(std::pair<std::string,std::string>("pos_x",lexical_cast<std::string>(GetPos().GetX())));
    m.insert(std::pair<std::string,std::string>("pos_y",lexical_cast<std::string>(GetPos().GetY())));
    m.insert(std::pair<std::string,std::string>("angle",lexical_cast<std::string>(GetAngle())));
    m.insert(std::pair<std::string,std::string>("color",lexical_cast<std::string>(GetColor())));
    m.insert(std::pair<std::string,std::string>("length",lexical_cast<std::string>(GetLength())));

    return m;
}

// std::map<std::string, std::string> ShapeGroup::ToMap()
// {
//     std::map<std::string, std::string> m;
//     m.insert(std::pair<std::string,std::string>("type", typeid(this).name()));
//     m.insert(std::pair<std::string,std::string>("pos_x",lexical_cast<std::string>(GetPos().GetX())));
//     m.insert(std::pair<std::string,std::string>("pos_y",lexical_cast<std::string>(GetPos().GetY())));
//     m.insert(std::pair<std::string,std::string>("angle",lexical_cast<std::string>(GetAngle())));
//     m.insert(std::pair<std::string,std::string>("color",lexical_cast<std::string>(GetColor())));
//     m.insert(std::pair<std::string,std::string>("group_size",lexical_cast<std::string>(GetGroupSize())));


//     for_each(m_list.begin(), m_list.end(), to_map_each);

//     return m;
// }

} //namespace ilrd