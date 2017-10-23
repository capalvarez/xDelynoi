#ifndef XDELYNOI_POINTCREATOR_H
#define XDELYNOI_POINTCREATOR_H

#include <delynoi/models/basic/Point.h>
#include <xDelynoi/models/xPolygon.h>

class PointCreator{
public:
    virtual std::vector<Point> createPoints(xPolygon poly, UniqueList<Point> points)=0;
};

#endif
