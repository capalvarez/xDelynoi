#include <xDelynoi/operations/break/closingrules/TriangulateClosingRule.h>

void TriangulateClosingRule::closePolygon(xMesh *mesh, Point p, int polygon, NeighbourInfo info) {
    UniqueList<Point>& points = mesh->getPoints();
    int index;

    if(info.edge.isInCorner(p, points.getList(), index)){
        return;
    }

    xPointMap& pointMap = mesh->getPointMap();
    xSegmentMap& segmentMap = mesh->getSegments();
    xPolygon* poly = mesh->getPolygon(polygon);

    ElementConstructor* constructor = new xTriangleConstructor();

    int pIndex = points.push_back(p);
    int p1Index = points.push_back(info.intersection);

    std::vector<IndexSegment> restricted;

    if(!info.edge.contains(points.getList(), p)){
        restricted.push_back(IndexSegment(p1Index, p1Index));
    }

    Region r (*poly, points.getList());
    TriangleDelaunayGenerator generator(r, std::vector<Point>());
    Mesh<Triangle> triangulation = generator.getConstrainedDelaunayTriangulation(restricted);

    SimpleMesh meshToInclude(triangulation.getPolygons(), triangulation.getPoints());

    std::unordered_map<int,int> triangulationMap = AddElementsAdapter::includeNewPoints(points, mesh->getPoints());
    AddElementsAdapter::includeNewElements(mesh, meshToInclude, triangulationMap, polygon, constructor);

    delete constructor;
}
