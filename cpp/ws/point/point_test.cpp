#include <stdio.h>

#include "point.hpp"

int main()
{
    Point p1, p2, p3;

    p1.x = 1;
    p1.y = 2;

    p2.x = 3;
    p2.y = 4;

    p3.x = 5;
    p3.y = 6;

    p1.AdjustBy(p2).AdjustBy(p3).AdjustBy(3,8);

    p1.Print(Point::ROUND);
}