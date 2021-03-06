#ifndef XDELYNOI_MESHMERGER_H
#define XDELYNOI_MESHMERGER_H

#include "MeshOperator.h"
#include <vector>
#include <delynoi/models/basic/Point.h>
#include <xDelynoi/models/xPolygon.h>

class MeshMerger : public MeshOperator {
public:
    virtual std::vector<int> mergeElements(xPolygon e1, xPolygon e2)=0;
    virtual std::vector<int> mergeElements(xPolygon e1, xPolygon e2, IndexSegment segment)=0;
    virtual std::vector<int> mergeElements(std::vector<int> elements)=0;
    virtual MeshOperator* clone()=0;
};

#endif