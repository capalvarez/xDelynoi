#ifndef XDELYNOI_DELAUNAYTRIANGULATIONGENERATOR_H
#define XDELYNOI_DELAUNAYTRIANGULATIONGENERATOR_H


#include "PointCreator.h"

class DelaunayPointCreator : public PointCreator{
public:
    std::vector<Point> createPoints(xPolygon poly, UniqueList<Point> points);
};


#endif