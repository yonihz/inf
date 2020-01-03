// compile command:
// gcc demo.c -I ./include -Wl,-rpath=. ./lib/libglut_utils.so

#include <cstdio>
#include <mcheck.h>

#include "shape.hpp"

using namespace ilrd;

int drawCircle = 1;
int xCircle = 250;
int yCircle = 100;
double rCircle = 100;

static void DrawFunction1();
static void DrawFunction2();
static void DrawFunction3();
static void DrawFunction4();
static int KeyboardFunction(unsigned char key, int x, int y);
static int MouseFunction(int button, int state, int x, int y);
static int MotionFunction(int x, int y);
static int TimerFunction();


int main(int argc, char** argv)
{
    /*--------------------------- mtrace(); */

    DrawInit(argc, argv, 1000, 1000, DrawFunction2);

    /* advanced: extra functionality */
    DrawSetKeyboardFunc(KeyboardFunction);
    DrawSetMouseFunc(MouseFunction);
    DrawSetMotionFunc(MotionFunction);
    DrawSetTimerFunc(TimerFunction, 100);

    DrawMainLoop();

    printf("exit\n");

    return 0;
}


static void DrawFunction1()
{
    /* printf("Drawing\n"); */

    // /* draw rectangle */
    // DrawPolygon(COLOR_MAGENTA, 4, (int)150, (int)400, (int)150, (int)650, (int)300, (int)650, (int)300, (int)400);

    // if (drawCircle)
    //     DrawCircle(COLOR_GREEN, xCircle, yCircle, rCircle);

    Circle c1(50, Point(250,500), 0, COLOR_BLUE);
    Circle c2(50, Point(500,500), 0, COLOR_GREEN);
    Circle c3(50, Point(100,500), 0, COLOR_GREEN);
    Circle c4(50, Point(900,500), 0, COLOR_GREEN);
    Circle c5(50, Point(500,100), 0, COLOR_GREEN);
    Circle c6(50, Point(500,900), 0, COLOR_GREEN);

    c1.Draw();
    c2.Draw();
    c3.Draw();
    c4.Draw();
    c5.Draw();
    c6.Draw();

    c1.Revolve(Point(500,500), 3.14/2);

    c1.Draw();
}

static void DrawFunction2()
{
    /* printf("Drawing\n"); */

    // /* draw rectangle */
    // DrawPolygon(COLOR_MAGENTA, 4, (int)150, (int)400, (int)150, (int)650, (int)300, (int)650, (int)300, (int)400);

    // if (drawCircle)
    //     DrawCircle(COLOR_GREEN, xCircle, yCircle, rCircle);

    Rectangle rec1(50, 100, Point(500,500), 0, COLOR_BLUE);

    rec1.Draw();

    rec1.Revolve(Point(500,500), 3.14/2);

    rec1.Draw();
}


static int KeyboardFunction(unsigned char key, int x, int y)
{
    printf("Keyboard: %02x,%d,%d\n", key, x, y);

    if (key == 0x1b /* ESC */)
        return -1;

    return 0;
}


static int MouseFunction(int button, int state, int x, int y)
{
    /* printf("Mouse: %d,%d,%d,%d\n", button, state, x, y); */

    // if (state == 1 && button == MOUSE_WHEEL_UP)
    // {
    //     rCircle *= 1.1;
    //     return 1;
    // }
    // if (state == 1 && button == MOUSE_WHEEL_DOWN)
    // {
    //     rCircle *= 0.9;
    //     return 1;
    // }

    // if (button == MOUSE_LEFT)
    // {
    //     drawCircle = state;
    //     return 1;
    // }

    return 0;
}


static int MotionFunction(int x, int y)
{
    // printf("Mouse: %d,%d\n", x, y);

    return 0;
}


static int TimerFunction()
{
    // xCircle += 1;
    // yCircle += 1;

    return 1;  /* draw */
}
