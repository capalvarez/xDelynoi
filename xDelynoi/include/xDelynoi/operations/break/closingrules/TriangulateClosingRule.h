#ifndef XDELYNOI_TRIANGULATECLOSINGRULE_H
#define XDELYNOI_TRIANGULATECLOSINGRULE_H

#include <xDelynoi/operations/break/closingrules/ClosingRule.h>
#include <xDelynoi/operations/refine/TriangulateRefiner.h>

class TriangulateClosingRule : public ClosingRule {
public:
    void closePolygon(xMesh* mesh, Point p, int polygon, NeighbourInfo info);
};

#endif