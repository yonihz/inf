// compile command:
// gd98 shape_test.cpp shape.cpp -Iinclude -I ../include -Wl,-rpath=. ./lib/libglut_utils.so -L./lib -lpoint
// install glut: sudo apt-get install freeglut3

#include <cstdio>
#include <mcheck.h>

#include "shape.hpp"

#define UNUSED(x) (void)(x)

using namespace ilrd;

int drawCircle = 1;
int xCircle = 250;
int yCircle = 100;
double rCircle = 100;

static void DrawFunction1();
static void DrawFunction2();
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

    Rectangle rec1(50, 100, Point(500,500), 0, COLOR_BLUE);
    Square sq1(50, Point(500,250), 0, COLOR_MAGENTA);
    Line line1(50, Point(500,750), 0, COLOR_YELLOW);
    Circle c1(50, Point(250,500));

    sq1.Draw();
    rec1.Draw();
    c1.Draw();
    line1.Draw();

    sq1.Revolve(Point(500,500), 3.14/4);
    rec1.Revolve(Point(500,500), 3.14/2);
    line1.Revolve(Point(500,750), 3.14*3/4);
    c1.Revolve(Point(500,500), 3.14/2);

    c1.Draw();
    rec1.Draw();
    sq1.Draw();
    line1.Draw();
}

static void DrawFunction2()
{
    ShapeGroup group1;
    group1.SetPos(Point(500,500));
    Rectangle rec1(50, 100, Point(500,500), 0, COLOR_BLUE);
    Circle c1(25, Point(500,425));
    Line l1(50, Point(450,480), 0, COLOR_YELLOW);
    Line l2(50, Point(550,480), 0, COLOR_YELLOW);
    Line l3(50, Point(485,575), 3.14/2, COLOR_YELLOW);
    Line l4(50, Point(515,575), 3.14/2, COLOR_YELLOW);

    group1.Add(&rec1);
    group1.Add(&c1);
    group1.Add(&l1);
    group1.Add(&l2);
    group1.Add(&l3);
    group1.Add(&l4);

    group1.Draw();

    group1.SetPos(group1.GetPos() + Point(0,-300));

    group1.Draw();

    group1.SetAngle(group1.GetAngle() + 3.14/2);

    group1.Draw();
    
    group1.Revolve(Point(500,500), 3.14/4);

    group1.Draw();

    group1.Revolve(Point(500,500), 3.14/4);

    group1.Draw();

    group1.SetAngle(group1.GetAngle() + 3.14/2);

    group1.Draw();
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

    UNUSED(button);
    UNUSED(state);
    UNUSED(x);
    UNUSED(y);

    return 0;
}


static int MotionFunction(int x, int y)
{
    // printf("Mouse: %d,%d\n", x, y);

    UNUSED(x);
    UNUSED(y);

    return 0;
}


static int TimerFunction()
{
    // xCircle += 1;
    // yCircle += 1;

    return 1;  /* draw */
}
