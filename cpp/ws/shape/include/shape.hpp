#ifndef __OL734_SHAPE_HPP__
#define __OL734_SHAPE_HPP__

/* Rev. 1.1 */ 
/* 02.01.20  11:00 */

#include <list> //list
#include <cstdlib> //size_t

#include "point.hpp"    // Point
#include "glut_utils.h"     // colors
 
namespace ilrd
{
  
class Shape
{
public:
    Shape(const Point& pos_, double angle_, COLORS color_);
    virtual ~Shape();
    virtual void Draw() =0;
    virtual void SetPos(const Point& pos_);
    const Point& GetPos() const;
    virtual void SetAngle(double angle_);
    double GetAngle() const;
    virtual void SetColor(COLORS color_);
    COLORS GetColor() const;
    void Revolve(const Point& pivot_, double angle_);
    virtual std::map<std::string, std::string> ToMap() = 0;
protected:
    Point m_position;
    double m_angle;
    COLORS m_color;
};
 
class Circle : public Shape
{
public:
    Circle(int radius_ = 1, const Point& pos_ = Point(), double angle_ = 0, COLORS color_ = COLOR_RED);
    ~Circle();
    void SetRadius(int radius_);
    int GetRadius() const;
    virtual void Draw();
    std::map<std::string, std::string> ToMap();
private:
    int m_radius;
};
 
class Rectangle : public Shape
{
public:
    Rectangle(int width_ = 1, int height_ = 1, const Point& pos_ = Point(), double angle_ = 0, COLORS color_ = COLOR_RED);
    ~Rectangle();
    void SetWidth(int width_);
    int GetWidth() const;
    void SetHeight(int height_);
    int GetHeight() const;
    virtual void Draw();
    std::map<std::string, std::string> ToMap();
private:
    int m_width;
    int m_height;
};
 
class Square : public Shape
{
public:
    Square(int side_ = 1, const Point& pos_ = Point(), double angle_ = 0, COLORS color_ = COLOR_RED);
    ~Square();
    void SetSide(int side_);
    int GetSide() const;
    virtual void Draw();
    std::map<std::string, std::string> ToMap();
private:
    int m_side;
};
 
class Line : public Shape
{
public:
    Line(int length_ = 1, const Point& pos_ = Point(), double angle_ = 0, COLORS color_ = COLOR_RED);
    ~Line();
    void SetLength(int length_);
    int GetLength() const;
    virtual void Draw();
    std::map<std::string, std::string> ToMap();
private:
    int m_length;
};
 
class ShapeGroup : public Shape
{
public:
    ShapeGroup();
    ~ShapeGroup();
    virtual void Draw();
    void Add(Shape* to_add_);
    void Remove(Shape* to_remove_);
    virtual void SetPos(const Point& pos_);
    virtual void SetAngle(double angle_);
    virtual void SetColor(COLORS color_);
    size_t GetGroupSize() const;
private:
    std::list<Shape*> m_list;
    size_t m_group_size; // cache
};

} // namespace ilrd

#endif /* __OL734_SHAPE_HPP__ */
 
