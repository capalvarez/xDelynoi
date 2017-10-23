#ifndef XDELYNOI_EARTRIANGULATIONGENERATOR_H
#define XDELYNOI_EARTRIANGULATIONGENERATOR_H


#include "PointCreator.h"

class EarPointCreator: public PointCreator{
public:
    std::vector<Point> createPoints(xPolygon poly, UniqueList<Point> points);
};


#endif
