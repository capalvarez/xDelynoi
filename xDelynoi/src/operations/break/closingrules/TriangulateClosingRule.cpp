#include <xDelynoi/operations/break/closingrules/TriangulateClosingRule.h>


void TriangulateClosingRule::closePolygon(xMeshElements& mesh, Point p, int polygon, NeighbourInfo info) {
    UniqueList<Point>& points = mesh.points;
    int index;

    if(info.edge.isInCorner(p, points.getList(), index)){
        return;
    }

    xPointMap* pointMap = mesh.pointMap;
    xSegmentMap* segmentMap = mesh.segments;
    xPolygon poly = mesh.polygons[polygon];

    int pIndex = points.push_back(p);
    int p1Index = points.push_back(info.intersection);

    std::vector<IndexSegment> restricted;

    if(!info.edge.contains(points.getList(), p)){
        restricted.push_back(IndexSegment(p1Index, p1Index));
    }

    Region r (poly, points.getList());
    TriangleDelaunayGenerator generator(r, std::vector<Point>());
    Mesh<Triangle> triangulation = generator.getConstrainedDelaunayTriangulation(restricted);

    SimpleMesh meshToInclude(triangulation.getPolygons(), triangulation.getPoints());

    std::unordered_map<int,int> triangulationMap = AddElementsAdapter::includeNewPoints(points, points.getList());
    AddElementsAdapter::includeNewElements(mesh, meshToInclude, triangulationMap, polygon);
}
