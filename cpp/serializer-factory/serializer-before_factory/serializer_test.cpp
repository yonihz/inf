// compile command:
// gd98 serializer_test.cpp ../shape/shape.cpp -I../shape/include -Wl,-rpath=. ../shape/lib/libglut_utils.so -L../shape/lib -lpoint

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <boost/lexical_cast.hpp>

#include "serializer.hpp"
#include "shape.hpp"

using namespace ilrd;
using boost::lexical_cast;

int main()
{
    Rectangle rec1(50, 100, Point(500,500), 0, COLOR_BLUE);
    Square sq1(50, Point(500,250), 0, COLOR_MAGENTA);
    Line line1(50, Point(500,750), 0, COLOR_YELLOW);
    Circle c1(50, Point(250,500));

    std::vector<Shape*> shape_instances;
    
    shape_instances.push_back(&rec1);
    shape_instances.push_back(&sq1);
    shape_instances.push_back(&line1);
    shape_instances.push_back(&c1);

    {
        std::fstream fs("myfile.json", std::ios::out | std::ios::app);
        Serializer<Shape> shape_serializer(fs);
        shape_serializer.Serialize(shape_instances);
    }
}