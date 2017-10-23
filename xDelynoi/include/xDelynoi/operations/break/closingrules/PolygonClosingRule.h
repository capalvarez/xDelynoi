#ifndef XDELYNOI_POLYGONCLOSINGRULE_H
#define XDELYNOI_POLYGONCLOSINGRULE_H

#include <xDelynoi/operations/break/closingrules/ClosingRule.h>
#include <xDelynoi/models/structures/NeighbourInfo.h>

class PolygonClosingRule : public ClosingRule{
protected:
    virtual Point getClosingPoint(IndexSegment segment, UniqueList<Point> points, Point intersection) = 0;
public:
    void closePolygon(xMeshElements& mesh, Point p, int polygon, NeighbourInfo info);
};

#endif