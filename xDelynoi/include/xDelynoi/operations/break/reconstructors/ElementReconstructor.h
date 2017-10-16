#ifndef XDELYNOI_ELEMENTRECONSTRUCTOR_H
#define XDELYNOI_ELEMENTRECONSTRUCTOR_H

#include <xDelynoi/models/xPolygon.h>

class ElementReconstructor {
public:
    virtual std::vector<xPolygon> reconstructElement(std::vector<int> points, std::vector<Point> meshPoints) = 0;
};

#endif