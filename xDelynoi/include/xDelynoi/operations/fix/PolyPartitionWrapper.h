#ifndef XDELYNOI_POLYPARTITIONWRAPPER_H
#define XDELYNOI_POLYPARTITIONWRAPPER_H

#include <vector>
#include <xDelynoi/models/xPolygon.h>
#include <xDelynoi/models/xMesh.h>
#include <xDelynoi/lib/polypartition.h>

class PolyPartitionWrapper {
private:
    xMesh* mesh;
    ElementConstructor* constructor;
public:
    PolyPartitionWrapper(xMesh* mesh, ElementConstructor* constructor);

    std::vector<xPolygon*> partition(xPolygon* elem);
};

#endif