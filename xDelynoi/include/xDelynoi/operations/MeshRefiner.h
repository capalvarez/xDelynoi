#ifndef XDELYNOI_MESHREFINER_H
#define XDELYNOI_MESHREFINER_H

#include <xDelynoi/models/xPolygon.h>
#include <xDelynoi/models/xMesh.h>
#include <delynoi/models/Region.h>
#include <delynoi/voronoi/TriangleDelaunayGenerator.h>
#include <xDelynoi/operations/adapter/AddElementsAdapter.h>
#include <xDelynoi/operations/refine/structures/SimpleMesh.h>

class xMesh;

class MeshRefiner{
protected:
    xMesh* mesh;
    ElementConstructor* constructor;
public:
    MeshRefiner(xMesh* mesh, ElementConstructor* constructor);

    void refine(xPolygon* elem, std::vector<Point> pointsToAdd);
    virtual SimpleMesh computeElements(xPolygon *elem, std::vector<Point> toAdd)=0;
};

#endif