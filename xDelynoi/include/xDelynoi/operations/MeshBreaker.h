#ifndef XDELYNOI_MESHBREAKER_H
#define XDELYNOI_MESHBREAKER_H

#include <xDelynoi/models/xMesh.h>
#include <xDelynoi/operations/break/closingrules/ClosingRule.h>
#include <xDelynoi/models/xPolygon.h>
#include <xDelynoi/operations/break/reconstructors/ElementReconstructor.h>

class xMesh;
class ClosingRule;

class MeshBreaker{
private:
    xMesh* mesh;
    ClosingRule* closingRule;
    ElementReconstructor* constructor;

    void breakMesh(PointSegment segment, ClosingRule* closingRule);
public:
    MeshBreaker(xMesh *mesh, ClosingRule *close, ElementReconstructor *reconstructor);
    void breakMesh(PointSegment segment);
    void breakMesh(std::vector<PointSegment> segments);
    void breakPolygons(NeighbourInfo n1, NeighbourInfo &n2, int init);
};

#endif