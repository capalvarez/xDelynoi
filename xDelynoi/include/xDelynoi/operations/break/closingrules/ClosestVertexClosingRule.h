#ifndef XDELYNOI_CLOSESTVERTEXCLOSIGRULE_H
#define XDELYNOI_CLOSESTVERTEXCLOSIGRULE_H

#include <xDelynoi/operations/break/closingrules/ClosingRule.h>

class ClosestVertexClosingRule : public ClosingRule{
public:
    void closePolygon(xMesh* mesh, Point p, int polygon);
};

#endif