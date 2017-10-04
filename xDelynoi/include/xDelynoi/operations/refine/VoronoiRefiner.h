#ifndef XDELYNOI_VORONOIREFININGRULE_H
#define XDELYNOI_VORONOIREFININGRULE_H

#include <xDelynoi/operations/MeshRefiner.h>
#include <delynoi/voronoi/TriangleVoronoiGenerator.h>

class VoronoiRefiner : public MeshRefiner{
public:
    VoronoiRefiner(xMesh* mesh, ElementConstructor* constructor);
    SimpleMesh computeElements(xPolygon *elem, std::vector<Point> toAdd, std::unordered_map<int, int>& pointMap);

    std::unordered_map<int,int> addPoints(UniqueList<Point>& points, std::vector<Point> pointsToAdd);
};

#endif