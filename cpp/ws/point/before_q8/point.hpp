#ifndef ILRD_OL734_POINT_HPP
#define ILRD_OL734_POINT_HPP

struct Point
{
    enum ParenthesesType { ROUND, SQUARE, CURLY, ANGULAR };
    
    void AdjustBy(Point *p);
    void AdjustBy(int dx, int dy);
    double Length();
    void Print(char opening, char closing);
    void Print(enum ParenthesesType ptype);

    int x;
    int y;                                                                                     
};

Point Add(Point *p1, Point *p2);

#endif