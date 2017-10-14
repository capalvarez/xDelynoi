#ifndef XDELYNOI_PARTITIONER_H
#define XDELYNOI_PARTITIONER_H

#include <xDelynoi/operations/refine/structures/SimpleMesh.h>

template <class T>
class Partitioner{
public:
    virtual SimpleMesh<T> partition(xPolygon* elem)=0;
};

#endif