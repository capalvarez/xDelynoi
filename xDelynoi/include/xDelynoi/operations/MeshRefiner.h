#ifndef XDELYNOI_MESHREFINER_H
#define XDELYNOI_MESHREFINER_H

#include <xDelynoi/models/xPolygon.h>
#include <xDelynoi/models/xMesh.h>
#include <delynoi/models/Region.h>
#include <delynoi/voronoi/TriangleDelaunayGenerator.h>
#include <xDelynoi/operations/refine/RefineAdapter.h>

class MeshRefiner{
protected:
    xMesh* mesh;
    ElementConstructor* constructor;
public:
    MeshRefiner(xMesh* mesh, ElementConstructor* constructor);

    void refine(xPolygon* elem, std::vector<Point> pointsToAdd);

    virtual std::unordered_map<int,int> addPoints(UniqueList<Point>& points, std::vector<Point> pointsToAdd);
    virtual SimpleMesh computeElements(xPolygon *elem, std::vector<Point> toAdd, std::unordered_map<int, int>& pointMap)=0;
};

#endif