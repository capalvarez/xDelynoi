#ifndef XDELYNOI_TRIANGULATECLOSINGRULE_H
#define XDELYNOI_TRIANGULATECLOSINGRULE_H

#include <xDelynoi/operations/break/closingrules/ClosingRule.h>
#include <xDelynoi/operations/refine/structures/SimpleMesh.h>
#include <xDelynoi/operations/adapter/AddElementsAdapter.h>
#include <delynoi/models/Region.h>
#include <delynoi/voronoi/TriangleDelaunayGenerator.h>


class TriangulateClosingRule : public ClosingRule {
public:
    void closePolygon(xMeshElements& mesh, Point p, int polygon, NeighbourInfo info);
};

#endif