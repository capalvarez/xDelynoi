#include <xDelynoi/operations/break/closingrules/PolygonClosingRule.h>

void PolygonClosingRule::closePolygon(xMesh *mesh, Point p, int polygon, NeighbourInfo info) {
    UniqueList<Point>& points = mesh->getPoints();

    if(info.edge.contains(points.getList(), p)){
        return;
    }

    xSegmentMap segmentMap = mesh->getSegments();
    xPolygon poly = mesh->getPolygon(polygon);

    std::vector<IndexSegment> segments;
    poly.getSegments(segments);

    IndexSegment intersected;
    Point intersection;

    for (IndexSegment s: segments){
        if(s.intersectionInfinite(points[s.getFirst()], points[s.getSecond()], p, info.intersection, intersection)){
            if (s == info.edge){
                continue;
            } else {
                intersected = s;
                break;
            }
        }
    }

    Point closingPoint = this->getClosingPoint(intersected, points, intersection);

    int pIndex = points.push_back(p);
    int p1Index = utilities::indexOf(points.getList(), info.intersection);
    int p2Index = points.push_back(closingPoint);

    std::vector<int> new1 = {p2Index, pIndex, p1Index};
    std::vector<int> new2 = {p1Index, pIndex, p2Index};

    NeighbourInfo n1 (segmentMap.getOther(intersected,polygon), intersected, intersection, false);

    MeshBreaker breaker(mesh, this);
    breaker.breakFromGivenSegment(n1, info, poly, new1, new2, p1Index, p2Index, -1);
}
