#ifndef XDELYNOI_CLOSINGRULE_H
#define XDELYNOI_CLOSINGRULE_H

#include <xDelynoi/models/xMesh.h>

class ClosingRule{
public:
    virtual void closePolygon(xMesh* mesh, Point p, int polygon, NeighbourInfo info)=0;
};

#endif