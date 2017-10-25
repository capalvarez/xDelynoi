#include <xDelynoi/operations/break/closingrules/StraightLineClosingRule.h>

bool StraightLineClosingRule::closingPointIsVertex() {
    return false;
}

Point StraightLineClosingRule::getClosingPoint(IndexSegment segment, UniqueList<Point> points, Point intersection) {
    return intersection;
}
