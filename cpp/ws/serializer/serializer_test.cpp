#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <boost/lexical_cast.hpp>

#include "serializer.hpp"
#include "shape.hpp"

using namespace ilrd;
using boost::lexical_cast;

boost::shared_ptr<Circle> CircleCreator(std::map<std::string, std::string> m)
{
    double pos_x = lexical_cast<double>(m["pos_x"]);
    double pos_y = lexical_cast<double>(m["pos_y"]);
    double angle = lexical_cast<double>(m["angle"]);
    COLORS color = static_cast<COLORS>(lexical_cast<int>(m["color"]));
    int radius = lexical_cast<int>(m["radius"]);
    boost::shared_ptr<Circle> c1(new Circle(radius, Point(pos_x, pos_y), angle, color));
    return c1;
}

int main()
{
    // Rectangle rec1(50, 100, Point(500,500), 0, COLOR_BLUE);
    // Square sq1(50, Point(500,250), 0, COLOR_MAGENTA);
    // Line line1(50, Point(500,750), 0, COLOR_YELLOW);
    Circle c1(50, Point(250,500));

    std::vector<Shape*> shape_instances;
    
    // shape_instances.push_back(&rec1);
    // shape_instances.push_back(&sq1);
    // shape_instances.push_back(&line1);
    shape_instances.push_back(&c1);

    std::ofstream ofs;
    ofs.open("myfile.txt", std::ofstream::out | std::ofstream::app);
    Serializer<Shape> shape_serializer(ofs);
    shape_serializer.Serialize(shape_instances);
    ofs.close();

}