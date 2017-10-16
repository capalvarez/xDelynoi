#ifndef XDELYNOI_POLYPARTITIONWRAPPER_H
#define XDELYNOI_POLYPARTITIONWRAPPER_H

#include <vector>
#include <xDelynoi/models/xPolygon.h>
#include <xDelynoi/models/xMesh.h>
#include <xDelynoi/lib/polypartition.h>
#include <xDelynoi/operations/fix/Partitioner.h>

class PolyPartitionWrapper : public Partitioner{
private:
    xMesh* mesh;
public:
    PolyPartitionWrapper(xMesh* mesh);

    SimpleMesh partition(xPolygon* elem);
};

#endif