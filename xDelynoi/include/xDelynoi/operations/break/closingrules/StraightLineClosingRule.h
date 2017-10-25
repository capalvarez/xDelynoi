#ifndef XDELYNOI_STRAIGHTLINECLOSINGRULE_H
#define XDELYNOI_STRAIGHTLINECLOSINGRULE_H

#include <xDelynoi/operations/break/closingrules/ClosingRule.h>
#include "PolygonClosingRule.h"

class StraightLineClosingRule : public PolygonClosingRule {
protected:
    bool closingPointIsVertex();
    Point getClosingPoint(IndexSegment segment, UniqueList<Point> points, Point intersection);
};

#endif