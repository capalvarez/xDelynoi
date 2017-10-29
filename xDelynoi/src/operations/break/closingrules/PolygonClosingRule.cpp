#include <xDelynoi/operations/break/closingrules/PolygonClosingRule.h>
#include <xDelynoi/operations/break/functions/break_functions.h>

void
PolygonClosingRule::closePolygon(xMeshElements *mesh, Point p, int polygon, NeighbourInfo info, bool previouslyBroken) {
    UniqueList<Point>* points = mesh->points;
    xPolygon poly = mesh->polygons->at(polygon);

    if(poly.inEdges(points->getList(), p) || previouslyBroken){
        return;
    }

    xSegmentMap* segmentMap = mesh->segments;

    std::vector<IndexSegment> segments;
    poly.getSegments(segments);

    IndexSegment intersected;
    Point intersection;
    PointSegment direction(p, info.intersection);

    for (IndexSegment s: segments){
        if(direction.intersectionInfinite(points->operator[](s.getFirst()), points->operator[](s.getSecond()), intersection)){
            if (s == info.edge){
                continue;
            } else {
                if(intersection == info.intersection){
                    continue;
                }
                intersected = s;
                break;
            }
        }
    }

    Point closingPoint = this->getClosingPoint(intersected, *points, intersection);

    int pIndex = points->push_back(p);
    int p1Index = utilities::indexOf(points->getList(), info.intersection);
    int p2Index = points->push_back(closingPoint);

    NeighbourInfo n1 (polygon, intersected, intersection, false);
    n1.isVertex = this->closingPointIsVertex();
    ElementReconstructor* reconstructor = new IdentityReconstructor();

    int p1 = n1.edge.contains(points->getList(), points->operator[](p1Index))? p1Index : p2Index;
    int p2 = p1 == p1Index? p2Index : p1Index;

    std::vector<int> new1 = {p1, pIndex, p2};
    std::vector<int> new2 = {p2, pIndex, p1};

    info.isVertex = true;

    break_functions::partitionPolygonFromSegment(mesh, reconstructor, n1, info, poly, new1, new2, p1, p2, segmentMap->getOther(intersected,polygon));
}
