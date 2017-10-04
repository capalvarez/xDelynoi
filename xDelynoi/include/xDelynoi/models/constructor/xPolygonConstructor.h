#ifndef XDELYNOI_XPOLYGONCONSTRUCTOR_H
#define XDELYNOI_XPOLYGONCONSTRUCTOR_H

#include <xDelynoi/models/xPolygon.h>
#include "ElementConstructor.h"

class xPolygonConstructor : public ElementConstructor{
public:
    xPolygon* createNewElement(std::vector<int> points, UniqueList<Point> meshPoints);
};

#endif