#ifndef ILRD_OL734_POINT_HPP
#define ILRD_OL734_POINT_HPP

struct Point
{
    enum ParenthesesType { ROUND, SQUARE, CURLY, ANGULAR };
    
    Point &AdjustBy(Point &p);
    Point &AdjustBy(int dx, int dy);
    double Length();
    void Print(char opening, char closing);
    void Print(enum ParenthesesType ptype);

    int x;
    int y;                                                                                     
};

Point Add(Point *p1, Point *p2);

#endif