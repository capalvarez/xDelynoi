#ifndef XDELYNOI_XTRIANGLE_H
#define XDELYNOI_XTRIANGLE_H

#include <delynoi/models/polygon/Triangle.h>
#include "xPolygon.h"

class xTriangle : public Triangle, public xPolygon {
public:
    xTriangle(Triangle triangle);
};

#endif