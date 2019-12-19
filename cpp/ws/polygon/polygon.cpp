#include <stdio.h>

#include "polygon.hpp"
#include "point.hpp"

Polygon::Polygon(size_t numPoints)
    : m_numPoints(numPoints)
{
    m_points = new Point[m_numPoints];
}

Polygon::~Polygon()
{
    delete[] m_points;
}

Polygon::Polygon(const Polygon& other_)
{
    size_t i = 0;
    
    for (i = 0; i < m_numPoints; i++)
    {
        m_points[i] = other_.m_points[i];
    }    
}

Polygon& Polygon::operator=(const Polygon& other_)
{
    size_t i = 0;
    
    for (i = 0; i < m_numPoints; i++)
    {
        m_points[i] = other_.m_points[i];
    }

    return *this;
}

void Polygon::Add(const Point &p)
{
    size_t i = 0;
    Point *new_m_points = new Point[m_numPoints + 1];

    for (i = 0; i < m_numPoints; i++)
    {
        m_points[i] = new_m_points[i];
    }

    new_m_points[m_numPoints] = p;
    
}

bool Polygon::IsEqual(const Polygon& other_) const
{
    size_t i = 0;
    bool is_equal = true;
    
    for (i = 0; i < m_numPoints && true == is_equal; i++)
    {
        is_equal = m_points[i].IsEqual(other_.m_points[i]);
    }

    return is_equal;
}

void Polygon::Print() const
{
    size_t i = 0;
    
    printf("Printing Polygon of %lu points:\n", m_numPoints);
    for (i = 0; i < m_numPoints; i++)
    {
        printf("Point %lu ", i);
        m_points[i].Print();
    }
}

