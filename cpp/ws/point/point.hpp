#ifndef ILRD_OL734_POINT_HPP
#define ILRD_OL734_POINT_HPP

extern double g_totalLength;

struct Point
{
    explicit Point();

    explicit Point(int dx, int dy);

    ~Point();

    enum ParenthesesType { ROUND, SQUARE, CURLY, ANGULAR };

    Point &AdjustBy(Point &p);
    Point &AdjustBy(int dx, int dy);
    double Length();
    void Print(char opening, char closing);
    void Print(ParenthesesType ptype = ROUND);
    bool IsEqual(Point &p);

    public:
        int x;
        int y; 

    private:
        double last_len;
        bool is_len_updated;                                                                                    
        int last_x;
        int last_y;
};

Point Add(Point *p1, Point *p2);

#endif