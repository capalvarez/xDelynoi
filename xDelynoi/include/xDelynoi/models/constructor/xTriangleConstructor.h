#ifndef XDELYNOI_XTRIANGLECONSTRUCTOR_H
#define XDELYNOI_XTRIANGLECONSTRUCTOR_H

#include <xDelynoi/models/xPolygon.h>
#include "ElementConstructor.h"

class xTriangleConstructor : public ElementConstructor {
public:
    xPolygon* createNewElement(std::vector<int> points, UniqueList<Point> meshPoints);
};

#endif