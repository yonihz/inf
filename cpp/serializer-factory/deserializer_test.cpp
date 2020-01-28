// compile command:
// gd98 gd98 deserializer_test.cpp ../shape/shape.cpp -I../shape/include -Wl,-rpath=. ../shape/lib/libglut_utils.so -L../shape/lib -lpoint -I../factory/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <mcheck.h>

#include <boost/lexical_cast.hpp>

#include "serializer.hpp"
#include "shape.hpp"

#define UNUSED(x) (void)(x)

using namespace ilrd;
using boost::lexical_cast;

int drawCircle = 1;
int xCircle = 250;
int yCircle = 100;
double rCircle = 100;

static void DrawFunction1();
static int KeyboardFunction(unsigned char key, int x, int y);
static int MouseFunction(int button, int state, int x, int y);
static int MotionFunction(int x, int y);
static int TimerFunction();

boost::shared_ptr<Shape> CircleCreator(std::map<std::string, std::string> m)
{
    double pos_x = lexical_cast<double>(m["pos_x"]);
    double pos_y = lexical_cast<double>(m["pos_y"]);
    double angle = lexical_cast<double>(m["angle"]);
    COLORS color = static_cast<COLORS>(lexical_cast<int>(m["color"]));
    int radius = lexical_cast<int>(m["radius"]);

    boost::shared_ptr<Shape> shape(new Circle(radius, Point(pos_x, pos_y), angle, color));
    shape->Draw();
    return shape;
}

boost::shared_ptr<Shape> RectangleCreator(std::map<std::string, std::string> m)
{
    double pos_x = lexical_cast<double>(m["pos_x"]);
    double pos_y = lexical_cast<double>(m["pos_y"]);
    double angle = lexical_cast<double>(m["angle"]);
    COLORS color = static_cast<COLORS>(lexical_cast<int>(m["color"]));
    int width = lexical_cast<int>(m["width"]);
    int height = lexical_cast<int>(m["height"]);

    boost::shared_ptr<Shape> shape(new Rectangle(width, height, Point(pos_x, pos_y), angle, color));
    shape->Draw();
    return shape;
}

boost::shared_ptr<Shape> SquareCreator(std::map<std::string, std::string> m)
{
    double pos_x = lexical_cast<double>(m["pos_x"]);
    double pos_y = lexical_cast<double>(m["pos_y"]);
    double angle = lexical_cast<double>(m["angle"]);
    COLORS color = static_cast<COLORS>(lexical_cast<int>(m["color"]));
    int side = lexical_cast<int>(m["side"]);

    boost::shared_ptr<Shape> shape(new Square(side, Point(pos_x, pos_y), angle, color));
    shape->Draw();
    return shape;
}

boost::shared_ptr<Shape> LineCreator(std::map<std::string, std::string> m)
{
    double pos_x = lexical_cast<double>(m["pos_x"]);
    double pos_y = lexical_cast<double>(m["pos_y"]);
    double angle = lexical_cast<double>(m["angle"]);
    COLORS color = static_cast<COLORS>(lexical_cast<int>(m["color"]));
    int length = lexical_cast<int>(m["length"]);

    boost::shared_ptr<Shape> shape(new Line(length, Point(pos_x, pos_y), angle, color));
    shape->Draw();
    return shape;
}

int main(int argc, char *argv[])
{
    /*--------------------------- mtrace(); */

    DrawInit(argc, argv, 1000, 1000, DrawFunction1);

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
    std::fstream fs("myfile.json", std::ios::in);
    Serializer<Shape> shape_serializer(fs);
    shape_serializer.AddType<Circle>(CircleCreator);
    shape_serializer.AddType<Rectangle>(RectangleCreator);
    shape_serializer.AddType<Square>(SquareCreator);
    shape_serializer.AddType<Line>(LineCreator);
    shape_serializer.Deserialize();
    fs.close();
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