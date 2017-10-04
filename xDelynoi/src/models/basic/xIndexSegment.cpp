#include <xDelynoi/models/basic/xIndexSegment.h>

xIndexSegment::xIndexSegment(int i1, int i2) : IndexSegment(i1,i2){}

bool xIndexSegment::isSegmentInBoundary(std::vector<Point> points) {
    return points[this->p1].isInBoundary() && points[this->p2].isInBoundary();
}
