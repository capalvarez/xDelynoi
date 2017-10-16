#ifndef XDELYNOI_PARTITIONER_H
#define XDELYNOI_PARTITIONER_H

#include <xDelynoi/operations/refine/structures/SimpleMesh.h>

class Partitioner{
public:
    virtual SimpleMesh partition(xPolygon elem)=0;
};

#endif