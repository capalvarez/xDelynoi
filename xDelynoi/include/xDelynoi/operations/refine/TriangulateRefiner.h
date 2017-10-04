#ifndef XDELYNOI_TRIANGULATEREFININGRULE_H
#define XDELYNOI_TRIANGULATEREFININGRULE_H

#include <xDelynoi/models/xPolygon.h>
#include <xDelynoi/models/xMesh.h>

class TriangulateRefiner : public MeshRefiner {
public:
    TriangulateRefiner(xMesh* mesh, ElementConstructor* constructor);
    SimpleMesh computeElements(xPolygon *elem, std::vector<Point> toAdd, std::unordered_map<int, int>& pointMap);
};

#endif