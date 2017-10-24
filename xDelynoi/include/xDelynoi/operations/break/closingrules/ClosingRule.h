#ifndef XDELYNOI_CLOSINGRULE_H
#define XDELYNOI_CLOSINGRULE_H

#include <xDelynoi/models/structures/NeighbourInfo.h>
#include <xDelynoi/models/structures/xMeshElements.h>

class ClosingRule{
public:
    virtual void closePolygon(xMeshElements* mesh, Point p, int polygon, NeighbourInfo info)=0;
};

#endif