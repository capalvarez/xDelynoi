#include <xDelynoi/operations/break/closingrules/TriangulateClosingRule.h>


void TriangulateClosingRule::closePolygon(xMeshElements* mesh, Point p, int polygon, NeighbourInfo info, bool previouslyBroken) {
    UniqueList<Point>* points = mesh->points;
    int index;

    if(info.edge.isInCorner(p, points->getList(), index) || previouslyBroken){
        return;
    }

    xPointMap* pointMap = mesh->pointMap;
    xSegmentMap* segmentMap = mesh->segments;
    xPolygon poly = mesh->polygons->at(polygon);

    std::vector<PointSegment> restricted;

    if(!info.edge.contains(points->getList(), p)){
        restricted.push_back(PointSegment(p, info.intersection));
    }

    Region r (poly, points->getList());
    std::vector<Point> pointsToInclude = {p};
    TriangleDelaunayGenerator generator(r, pointsToInclude);
    Mesh<Triangle> triangulation = generator.getConstrainedDelaunayTriangulation(restricted);

    SimpleMesh meshToInclude(triangulation.getPolygons(), triangulation.getPoints());

    std::unordered_map<int,int> triangulationMap = AddElementsAdapter::includeNewPoints(*points, meshToInclude.getPoints());
    AddElementsAdapter::includeNewElements(mesh, meshToInclude, triangulationMap, polygon);
}
