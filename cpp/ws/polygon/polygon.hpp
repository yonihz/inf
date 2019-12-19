#ifndef ILRD_OL734_POLYGON_HPP
#define ILRD_OL734_POLYGON_HPP

#include <stdlib.h>

#include "point.hpp"

struct Polygon {
    explicit Polygon(size_t numPoints = 0);
    
    ~Polygon();

    Polygon(const Polygon& other_);

    Polygon& operator=(const Polygon& other_);    

    void Add(const Point &p);
    bool IsEqual(const Polygon& other) const;
    void Print() const;

    size_t m_numPoints;
    Point *m_points;
};

#endif