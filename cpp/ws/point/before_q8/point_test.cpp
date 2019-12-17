#include <stdio.h>

#include "point.hpp"

int main()
{
    Point p1;
    Point p2;
    Point p3;

    p1.x = 1;
    p1.y = 2;

    p2.x = 10;
    p2.y = 20;

    printf("p1\n");
    p1.Print('(', ')');

    printf("p2\n");
    p2.Print('(', ')');

    printf("p3 after add\n");
    p3 = Add(&p1, &p2);
    p3.Print('(', ')');

    printf("p1 length %f, p2 length %f\n", p1.Length(), p2.Length());

    p1.AdjustBy(&p2);

    printf("p1.AdjustBy(&p2)\n");
    p1.Print('(', ')');

    printf("print p3 curly\n");
    p3.Print(Point::CURLY);
}