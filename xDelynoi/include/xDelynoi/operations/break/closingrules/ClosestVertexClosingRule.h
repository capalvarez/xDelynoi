#ifndef XDELYNOI_CLOSESTVERTEXCLOSIGRULE_H
#define XDELYNOI_CLOSESTVERTEXCLOSIGRULE_H

#include <xDelynoi/operations/break/closingrules/ClosingRule.h>
#include "PolygonClosingRule.h"

class ClosestVertexClosingRule : public PolygonClosingRule{
protected:
    Point getClosingPoint(IndexSegment segment, UniqueList<Point> points, Point intersection);
};

#endif