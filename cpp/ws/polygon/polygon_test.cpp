#include <stdio.h>

#include "polygon.hpp"

int main()
{
    size_t numPoints = 3;

    Point p1 (1, 2);
    Point p2 (3, 4);
    Point p3 (5, 6);

    printf("Polygon create poly1 (numPoints = 3)\n");
    Polygon poly1(numPoints);
    poly1.Print();
    
    printf("Polygon add point to poly1 (1, 2)\n");
    poly1.Add(p1);
    poly1.Print();

    printf("Polygon add point to poly1 (3, 4)\n");
    poly1.Add(p2);
    poly1.Print();

    printf("Polygon create poly2 (copy of poly1)\n");
    Polygon poly2(poly1);
    poly2.Print();

    printf("Check IsEqual(poly1, poly2): %d (should be 1)\n", poly1.IsEqual(poly2));
    printf("Polygon add point to poly2 (5, 6)\n");
    poly2.Add(p3);
    printf("Check IsEqual(poly1, poly2): %d (should be 0)\n", poly1.IsEqual(poly2));

    printf("Polygon create poly3 (numPoints = 5)\n");
    Polygon poly3(numPoints + 2);
    poly3.Print();
    printf("Print after poly3 = poly1\n");
    poly3 = poly1;
    poly3.Print();
}