#ifndef XDELYNOI_POLYGONTOTRIANGLECONSTRUCTOR_H
#define XDELYNOI_POLYGONTOTRIANGLECONSTRUCTOR_H

#include <vector>
#include <delynoi/models/basic/Point.h>
#include <xDelynoi/models/xPolygon.h>
#include "ElementReconstructor.h"

class PolygonToTriangleReconstructor: public ElementReconstructor {
public:
    std::vector<xPolygon> reconstructElement(std::vector<int> points, std::vector<Point> meshPoints);
};

#endif