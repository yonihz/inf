#include <stdio.h>
#include <math.h>

#include "point.hpp"

void TestCaching();
void TestTotalLength();

int main()
{
    //TestCaching();
    TestTotalLength();
}

void TestCaching()
{
    Point p1;
    Point p2(0, 0);
    Point p3(2, 4);
    Point p4(3, 9);

    p1.AdjustBy(p2).AdjustBy(p3).AdjustBy(3,8);

    p3.Print(Point::CURLY);
    p1.Print();

    printf("p3 is equal to p4: %d\n", p3.IsEqual(p4));
    printf("p2 is equal to p4: %d\n", p2.IsEqual(p4));

    p1.Print();
    printf("p1 length is: %f\n", p1.Length());
    p1.Print();
    printf("p1 length is: %f\n", p1.Length());
    p1.AdjustBy(1,4);
    p1.Print();
    printf("p1 length is: %f\n", p1.Length());
    p1.Print();
    printf("p1 length is: %f\n", p1.Length());

    p1.x = 1;
    p1.y = 2;
    p1.Print();
    printf("p1 length is: %f\n", p1.Length());
    p1.Print();
    printf("p1 length is: %f\n", p1.Length());
}

void TestTotalLength()
{
    Point p1;
    Point p2(0, 0);
    Point p3(3, 4); // length = 5
    Point p4(5, 12); // length = 13

    printf("Length: %f\n", p1.Length());
    printf("Length: %f\n", p2.Length());
    printf("Length: %f\n", p3.Length());
    printf("Length: %f\n", p4.Length());
    printf("Total length after init p1, p2, p3, p4: %f\n", g_totalLength);

    {
        Point p5(3, 4); // length = 13
        printf("Total length after init p5: %f\n", g_totalLength);
    }

    printf("Total length after de-init p5: %f\n", g_totalLength);


    p1.AdjustBy(1,1);
    printf("Total length after adjust p1: %f\n", g_totalLength);
    p1.AdjustBy(1,1);
    printf("Total length after adjust p1: %f\n", g_totalLength);
}