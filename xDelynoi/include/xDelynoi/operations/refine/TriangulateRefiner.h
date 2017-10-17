#ifndef XDELYNOI_TRIANGULATEREFININGRULE_H
#define XDELYNOI_TRIANGULATEREFININGRULE_H

#include <xDelynoi/operations/MeshRefiner.h>
#include <xDelynoi/models/xPolygon.h>
#include <xDelynoi/models/xMesh.h>
#include <delynoi/voronoi/TriangleDelaunayGenerator.h>
#include <xDelynoi/operations/refine/structures/SimpleMesh.h>

class TriangulateRefiner : public MeshRefiner {
public:
    TriangulateRefiner(xMesh* mesh);
    SimpleMesh computeElements(xPolygon elem, std::vector<Point> toAdd);
};

#endif