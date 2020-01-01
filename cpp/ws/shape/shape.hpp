#ifndef __OL734_SHAPES_HPP__
#define __OL734_SHAPES_HPP__

/* Rev. 1.0 */ 
/* 01.01.20  16:00 */

#include <list> //list
#include <cstdlib> //size_t

#include "point.hpp"    // Point
#include "glut_utils.h"     // colors
 
namespace ilrd
{
  
class Shape
{
public:
   Shape(Point pos_, double angle_, COLORS color_);
   virtual ~Shape();
   virtual void Draw() =0;
   void SetPos(Point& pos_);
   Point& GetPos();
   void SetAngle(double angle_);
   double GetAngle();
   void SetColor(COLORS color_);
   COLORS GetColor();
   void Revolve(Point pivot, double angle);
private:
   Point m_position;  
   double m_angle;
   COLORS m_color;
};
 
class Circle : public Shape
{
public:
   Circle(size_t radius_ = 1, Point pos_ = Point(), double angle_ = 0, COLORS color_ = COLOR_RED);
   ~Circle();
   void SetRadius(size_t radius_);
   size_t GetRadius();
   virtual void Draw();
private:
   size_t m_radius;
};
 
class Rectangle : public Shape
{
public:
   Rectangle(size_t width_ = 1, size_t height_ = 1, Point pos_ = Point(), double angle_ = 0, COLORS color_ = COLOR_RED);
   ~Rectangle();
   void SetWidth(size_t width_);
   size_t GetWidth();
   void SetHeight(size_t height_);
   size_t GetHeight();
   virtual void Draw();
private:
   size_t m_width;
   size_t m_height;
};
 
class Square : public Shape
{
public:
   Square(size_t side_ = 1, Point pos_ = Point(), double angle_ = 0, COLORS color_ = COLOR_RED);
   ~Square();
   void SetSide(size_t side_);
   size_t GetSide();
   virtual void Draw();
private:
   size_t m_side;
};
 
class Line : public Shape
{
public:
   Line(size_t length_ = 1, Point pos_ = Point(), double angle_ = 0, COLORS color_ = COLOR_RED);
   ~Line();
   void SetLength(size_t length_);
   size_t GetLength();
   virtual void Draw();
private:
   size_t m_length;
};
 
class ShapeGroup : public Shape
{
public:
   ShapeGroup(Point pos_ = Point(), double angle_ = 0, COLORS color_ = COLOR_RED);
   ~ShapeGroup();
   virtual void Draw();
   void Add(Shape* to_add_);
   void Remove(Shape* to_remove_);
   size_t GetGroupSize();
private:
   std::list<Shape*> m_arr;
   size_t m_group_size; //cache
};
 
 
} // namespace ilrd
 
 
 
#endif/* __OL734_SHAPES_HPP__ */
 
