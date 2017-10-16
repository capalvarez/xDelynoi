#ifndef XDELYNOI_XMESH_H
#define XDELYNOI_XMESH_H

#include <delynoi/models/Mesh.h>
#include <xDelynoi/models/structures/ContainerInfo.h>
#include <xDelynoi/models/structures/NeighbourInfo.h>
#include <xDelynoi/models/xPolygon.h>
#include <xDelynoi/models/neighbourhood/xSegmentMap.h>
#include <xDelynoi/models/neighbourhood/xPointMap.h>
#include <xDelynoi/operations/MeshMerger.h>
#include <xDelynoi/utilities/xdelynoi_utilities.h>
#include <xDelynoi/operations/MeshRefiner.h>
#include <xDelynoi/operations/MeshFixer.h>
#include <xDelynoi/operations/MeshBreaker.h>

class MeshBreaker;
class MeshRefiner;
class MeshFixer;
class ClosingRule;

class xMesh : public Mesh<xPolygon>{
private:
    xSegmentMap edges;
    xPointMap pointMap;

    MeshMerger* merger;
    MeshRefiner* refiner;
    MeshBreaker* breaker;
    MeshFixer* fixer;

    ContainerInfo processContainerInfo(int poly, Point point);
    void swapElements(int first, int second, std::unordered_map<IndexSegment, int, SegmentHasher> &toIgnore);
    void replaceElementsForMerged(std::vector<int> merged, std::vector<int> polys, std::vector<int> deletedPoints);
public:
    xMesh(Mesh<Polygon> mesh);
    xMesh(Mesh<Triangle> mesh);

    xSegmentMap& getSegments();
    xSegmentMap getSegments() const;
    xPointMap& getPointMap();
    xPointMap getPointMap() const;

    void breakMesh(PointSegment segment);
    void breakMesh(PointSegment segment, ClosingRule* closingRule);

    void erase(Point p);
    void erase(xPolygon elem);

    void swapElements(xPolygon elem1, xPolygon elem2);
    void swapElements(int elem1, int elem2);

    void swapPoints(int point1, int point2);
    void swapPoints(Point p1, Point p2);

    void mergeElements(int elem1, int elem2);
    void mergeElements(std::vector<int> elements);

    ContainerInfo findContainer(Point p);
    ContainerInfo findContainer(Point p, int startElement);
    ContainerInfo findContainerLinear(Point p);

    NeighbourInfo getNeighbour(int poly_index, PointSegment direction);
    NeighbourInfo getNeighbour(int poly_index, PointSegment direction, std::vector<int> &previous);
    int getNeighbourFromCommonVertexSet(PointSegment direction, std::vector<int> vertexSet, int vertexIndex);

    void refine(Point p);
    void refine(std::vector<Point> p);

    std::vector<int> getNeighboursByPoint(int poly_index);
    std::vector<int> getNeighboursBySegment(int poly_index);

    xPolygon getPolygon(int index);
    bool isInBorder(IndexSegment container);

    bool isEndPoint(IndexSegment segment, Point point);
};

#endif