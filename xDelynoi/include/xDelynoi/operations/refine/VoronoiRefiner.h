#ifndef XDELYNOI_VORONOIREFININGRULE_H
#define XDELYNOI_VORONOIREFININGRULE_H

#include <xDelynoi/operations/MeshRefiner.h>
#include <delynoi/voronoi/TriangleVoronoiGenerator.h>

class VoronoiRefiner : public MeshRefiner{
public:
    VoronoiRefiner();
    SimpleMesh computeElements(xPolygon elem, std::vector<Point> toAdd);
    MeshOperator* clone();
};

#endif