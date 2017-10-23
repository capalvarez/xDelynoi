#ifndef XDELYNOI_XMESH_H
#define XDELYNOI_XMESH_H

#include <xDelynoi/operations/MeshOperator.h>
#include <xDelynoi/operations/MeshMerger.h>
#include <xDelynoi/operations/MeshRefiner.h>
#include <xDelynoi/models/structures/ContainerInfo.h>
#include <xDelynoi/models/structures/NeighbourInfo.h>
#include "xPolygon.h"
#include <delynoi/models/Mesh.h>
#include <xDelynoi/models/neighbourhood/xPointMap.h>
#include <xDelynoi/operations/MeshBreaker.h>
#include <xDelynoi/operations/MeshFixer.h>
#include <xDelynoi/utilities/vector_ops.h>
#include <xDelynoi/utilities/xdelynoi_utilities.h>
#include <xDelynoi/models/structures/greater.h>
#include <xDelynoi/models/creator/PointCreator.h>
#include <delynoi/models/generator/PointGenerator.h>
#include <xDelynoi/config/Config.h>

class MeshOperator;
class MeshRefiner;
class MeshBreaker;
class MeshMerger;

class xMesh : public Mesh<xPolygon>{
private:
    xSegmentMap* xEdges;
    xPointMap* xpointMap;

    MeshMerger* merger;
    MeshBreaker* breaker;
    MeshRefiner* refiner;

    ContainerInfo processContainerInfo(int poly, Point point);
    void swapElements(int first, int second, std::unordered_map<IndexSegment, int, SegmentHasher> &toIgnore);
    int replaceElementsForMerged(std::vector<int> merged, std::vector<int> polys, std::vector<int> deletedPoints);
public:
    xMesh(Mesh<Triangle> mesh, Config config);
    xMesh(Mesh<Polygon> mesh, Config config);

    xSegmentMap* getSegments();
    xPointMap* getPointMap();

    ContainerInfo findContainer(Point p);
    ContainerInfo findContainer(Point p, int startElement);
    ContainerInfo findContainerLinear(Point p);

    NeighbourInfo getNeighbour(int poly_index, PointSegment direction);
    NeighbourInfo getNeighbour(int poly_index, PointSegment direction, std::vector<int> &previous);
    int getNeighbourFromCommonVertexSet(PointSegment direction, std::vector<int> vertexSet, int vertexIndex);

    std::vector<int> getNeighboursByPoint(int poly_index);
    std::vector<int> getNeighboursBySegment(int poly_index);

    bool isInBorder(IndexSegment container);
    bool isEndPoint(IndexSegment segment, Point point);

    void breakMesh(PointSegment segment);
    void breakMesh(std::vector<PointSegment> segments);

    void erase(Point p);
    void erase(xPolygon elem);

    void swapElements(xPolygon elem1, xPolygon elem2);
    void swapElements(int elem1, int elem2);

    void swapPoints(int point1, int point2);
    void swapPoints(Point p1, Point p2);

    void mergeElements(int elem1, int elem2);
    void mergeElements(std::vector<int> elements);

    void fix(MeshFixer* fixer);

    void refine(Point p);
    void refine(std::vector<Point> p);
    void refine(xPolygon poly, PointGenerator generator, int nX, int nY);
    void refine(xPolygon poly, PointCreator* generator);
};

#endif