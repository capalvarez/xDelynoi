#ifndef XDELYNOI_MESHREFINER_H
#define XDELYNOI_MESHREFINER_H

#include <xDelynoi/models/xPolygon.h>
#include <delynoi/models/Region.h>
#include <delynoi/voronoi/TriangleDelaunayGenerator.h>
#include <xDelynoi/operations/adapter/AddElementsAdapter.h>
#include <xDelynoi/operations/refine/structures/SimpleMesh.h>
#include "MeshOperator.h"

class MeshRefiner : public MeshOperator{
public:
    MeshRefiner();

    void refine(xPolygon elem, std::vector<Point> pointsToAdd);
    virtual SimpleMesh computeElements(xPolygon elem, std::vector<Point> toAdd)=0;
    virtual MeshOperator* clone()=0;
};

#endif