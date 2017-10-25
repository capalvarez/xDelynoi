#ifndef XDELYNOI_NOTALLOWEDMERGER_H
#define XDELYNOI_NOTALLOWEDMERGER_H

#include <xDelynoi/operations/MeshMerger.h>

class NotAllowedMerger: public MeshMerger {
public:
    std::vector<int> mergeElements(xPolygon e1, xPolygon e2);
    std::vector<int> mergeElements(xPolygon e1, xPolygon e2, IndexSegment segment);
    std::vector<int> mergeElements(std::vector<int> elements);
    MeshOperator* clone();
};

#endif