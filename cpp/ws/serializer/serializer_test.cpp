#include <iostream>
#include <string>
#include <vector>

#include <boost/lexical_cast.hpp>

#include "serializer.hpp"
#include "shape.hpp"

using namespace ilrd;
using boost::lexical_cast;

std::map<std::string, std::string> Circle::ToMap()
{
    std::map<std::string, std::string> m;

    m.insert(std::pair<std::string,std::string>("pos_x",lexical_cast<std::string>(GetPos().GetX())));
    m.insert(std::pair<std::string,std::string>("pos_y",lexical_cast<std::string>(GetPos().GetY())));
    m.insert(std::pair<std::string,std::string>("angle",lexical_cast<std::string>(GetAngle())));
    m.insert(std::pair<std::string,std::string>("color",lexical_cast<std::string>(GetColor())));
    m.insert(std::pair<std::string,std::string>("radius",lexical_cast<std::string>(GetRadius())));

    return m;
}

boost::shared_ptr<Circle> CircleCreator(std::map<std::string, std::string> m)
{
    double pos_x = lexical_cast<double>(m["pos_x"]);
    double pos_y = lexical_cast<double>(m["pos_y"]);
    double angle = lexical_cast<double>(m["angle"]);
    COLORS color = lexical_cast<COLORS>(m["color"]);
    int radius = lexical_cast<int>(m["radius"]);
    boost::shared_ptr<Circle> c1(new Circle(radius, Point(), double(0.0), color));
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


}