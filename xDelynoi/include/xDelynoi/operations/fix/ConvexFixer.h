#ifndef XDELYNOI_CONVEXFIXER_H
#define XDELYNOI_CONVEXFIXER_H

#include <xDelynoi/operations/MeshFixer.h>
#include <xDelynoi/operations/fix/Partitioner.h>
#include <xDelynoi/operations/adapter/AddElementsAdapter.h>

class ConvexFixer: public MeshFixer {
private:
    Partitioner* partitioner;

    void fixNonConvex(xPolygon elem);
public:
    ConvexFixer();
    ~ConvexFixer();
    void fixMesh();
    void fixElement(xPolygon elem);
    void setMesh(xMeshElements*& mesh);
    virtual MeshOperator* clone();
};

#endif