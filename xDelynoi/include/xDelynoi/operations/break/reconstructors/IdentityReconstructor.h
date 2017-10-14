#ifndef XDELYNOI_IDENTITYRECONSTRUCTOR_H
#define XDELYNOI_IDENTITYRECONSTRUCTOR_H

#include <vector>
#include <delynoi/models/basic/Point.h>
#include <xDelynoi/models/xPolygon.h>
#include <xDelynoi/models/constructor/ElementConstructor.h>
#include "ElementReconstructor.h"

class IdentityReconstructor: public ElementReconstructor {
public:
    IdentityReconstructor(ElementConstructor* constructor);
    std::vector<xPolygon*> reconstructElement(std::vector<int> points, UniqueList<Point> meshPoints);
};

#endif