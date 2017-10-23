#ifndef XDELYNOI_MESHBREAKER_H
#define XDELYNOI_MESHBREAKER_H

#include <xDelynoi/operations/break/closingrules/ClosingRule.h>
#include <xDelynoi/operations/break/reconstructors/ElementReconstructor.h>
#include <xDelynoi/models/structures/NeighbourInfo.h>
#include "MeshOperator.h"

class MeshBreaker: public MeshOperator{
private:
    ClosingRule* closingRule;
    ElementReconstructor* constructor;

    void breakMesh(PointSegment segment, ClosingRule* closingRule);
public:
    MeshBreaker(ClosingRule *close, ElementReconstructor *reconstructor);
    void breakMesh(PointSegment segment);
    void breakMesh(std::vector<PointSegment> segments);
    void breakPolygons(NeighbourInfo n1, NeighbourInfo &n2, int init);
};

#endif