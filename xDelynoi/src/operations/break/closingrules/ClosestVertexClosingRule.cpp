#include <xDelynoi/operations/break/closingrules/ClosestVertexClosingRule.h>

Point ClosestVertexClosingRule::getClosingPoint(IndexSegment segment, UniqueList<Point> points, Point intersection) {
    double distance1 = PointSegment(intersection, points[segment.getFirst()]).length();
    double distance2 = PointSegment(intersection, points[segment.getSecond()]).length();

    if (distance1 >= distance2){
        return points[segment.getFirst()];
    } else {
        return points[segment.getSecond()];
    }
}
