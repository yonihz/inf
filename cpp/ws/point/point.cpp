#include <stdio.h>
#include <math.h>

#include "point.hpp"

double g_totalLength = 0;

Point::Point()
    : x(0), y(0), last_len(0), is_len_updated(1), last_x(0), last_y(0)
{
    printf("Default Ctor\n");
}

Point::Point(int dx, int dy)
    : x(dx), y(dy), last_len(0), is_len_updated(0), last_x(dx), last_y(dy)
{
    g_totalLength += this->Length();
    printf("Ctor(int,int)\n");
}

Point::~Point()
{
    g_totalLength -= this->Length();
    printf("Dtor\n");
}

Point& Point::operator=(const Point& other_)
{
    x = other_.x;
    y = other_.y;

    return *this;
}

Point &Point::AdjustBy(Point &p)
{
    g_totalLength -= this->Length();
    x += p.x;
    y += p.y;
    is_len_updated = false;
    g_totalLength += this->Length();
    return *this;
}

Point &Point::AdjustBy(int dx, int dy)
{
    g_totalLength -= this->Length();
    x += dx;
    y += dy;
    is_len_updated = false;
    g_totalLength += this->Length();

    return *this;
}

double Point::Length()
{
    if (last_x != x || last_y != y)
    {
        is_len_updated = false;
    }

    if (false == is_len_updated)
    {
        last_x = x;
        last_y = y;
        is_len_updated = true;
        last_len = sqrt(pow(this->x, 2) + pow(this->y, 2));
    }

    return last_len;
}

void Point::Print(char opening, char closing)
{
    printf("%c%d, %d%c\n", opening, x, y, closing);
}

void Point::Print(ParenthesesType ptype)
{
    switch (ptype)
    {
        case ROUND:
        {
            printf("(%d, %d)\n", x, y);
            break;
        }
        case SQUARE:
        {
            printf("[%d, %d]\n", x, y);
            break;
        }
        case CURLY:
        {
            printf("{%d, %d}\n", x, y);
            break;
        }
        case ANGULAR:
        {
            printf("<%d, %d>\n", x, y);
            break;
        }
    }
}

bool Point::IsEqual(Point &p)
{
    if ((this->x == p.x) && (this->y == p.y))
    {
        return true;
    }
    else
    {
        return false;
    }
}

Point Add(Point *p1, Point *p2)
{
    Point p_new;
    p_new.x = p1->x + p2->x;
    p_new.y = p1->y + p2->y;

    return p_new;
}