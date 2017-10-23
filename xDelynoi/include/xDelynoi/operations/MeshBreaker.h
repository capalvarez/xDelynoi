#ifndef XDELYNOI_MESHBREAKER_H
#define XDELYNOI_MESHBREAKER_H

#include <xDelynoi/operations/break/closingrules/ClosingRule.h>
#include <xDelynoi/operations/break/reconstructors/ElementReconstructor.h>
#include <xDelynoi/models/structures/NeighbourInfo.h>
#include <xDelynoi/models/xMesh.h>
#include "MeshOperator.h"

class xMesh;

class MeshBreaker: public MeshOperator{
private:
    ClosingRule* closingRule;
    ElementReconstructor* constructor;

    void breakMesh(xMesh* mesh, PointSegment segment, ClosingRule* closingRule);
public:
    MeshBreaker(ClosingRule *close, ElementReconstructor *reconstructor);
    void breakMesh(xMesh* mesh, PointSegment segment);
    void breakMesh(xMesh* mesh, std::vector<PointSegment> segments);
    void breakPolygons(NeighbourInfo n1, NeighbourInfo &n2, int init);
};

#endif