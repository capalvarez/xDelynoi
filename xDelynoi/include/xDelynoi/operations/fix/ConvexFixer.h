#ifndef XDELYNOI_CONVEXFIXER_H
#define XDELYNOI_CONVEXFIXER_H

#include <xDelynoi/operations/MeshFixer.h>
#include <xDelynoi/operations/fix/Partitioner.h>

class ConvexFixer: public MeshFixer {
private:
    Partitioner* partitioner;
    ElementConstructor* constructor;
    xMesh* mesh;

    void fixNonConvex(xPolygon* elem);
public:
    ConvexFixer(xMesh *mesh, ElementConstructor* constructor);
    ~ConvexFixer();
    void fixMesh();
    void fixElement(xPolygon *elem);
};

#endif