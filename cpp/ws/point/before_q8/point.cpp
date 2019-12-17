#include <stdio.h>
#include <math.h>

#include "point.hpp"

void Point::AdjustBy(struct Point *p)
{
    this->x += p->x;
    this->y += p->y;
}

void Point::AdjustBy(int dx, int dy)
{
    this->x += dx;
    this->y += dy;
}

double Point::Length()
{
    return (sqrt(pow(this->x, 2) + pow(this->y, 2))); 
}

void Point::Print(char opening, char closing)
{
    printf("%c%d, %d%c\n", opening, x, y, closing);
}

void Point::Print(enum ParenthesesType ptype)
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

Point Add(Point *p1, Point *p2)
{
    Point p_new;
    p_new.x = p1->x + p2->x;
    p_new.y = p1->y + p2->y;

    return p_new;
}