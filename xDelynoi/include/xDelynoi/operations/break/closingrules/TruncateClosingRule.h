#ifndef XDELYNOI_TRUNCATECLOSINGRULE_H
#define XDELYNOI_TRUNCATECLOSINGRULE_H

#include "ClosingRule.h"

class TruncateClosingRule : public ClosingRule {
public:
    void closePolygon(xMeshElements *mesh, Point p, int polygon, NeighbourInfo info, bool previouslyBroken);
};

#endif