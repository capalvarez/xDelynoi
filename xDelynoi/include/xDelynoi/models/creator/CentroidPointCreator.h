#ifndef XDELYNOI_POLYGONCENTROIDGENERATOR_H
#define XDELYNOI_POLYGONCENTROIDGENERATOR_H

#include "PointCreator.h"

class CentroidPointCreator : public PointCreator {
public:
    std::vector<Point> createPoints(xPolygon poly, UniqueList<Point> points);
};

#endif
