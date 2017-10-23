#ifndef XDELYNOI_VERTEXINDEXMERGER_H
#define XDELYNOI_VERTEXINDEXMERGER_H

#include <delynoi/models/basic/Point.h>
#include <xDelynoi/models/xPolygon.h>
#include <xDelynoi/operations/MeshMerger.h>


class VertexIndexMerger: public MeshMerger {
private:
    bool areMergeable(xPolygon poly1, int poly2);
    std::vector<int> merge(xPolygon e1, xPolygon e2, Pair<int> endPoints, bool special_case);
public:
    VertexIndexMerger();
    std::vector<int> mergeElements(xPolygon e1, xPolygon e2, IndexSegment endPoints);
    std::vector<int> mergeElements(xPolygon e1, xPolygon e2);
    std::vector<int> mergeElements(std::vector<int> elements);
};

#endif