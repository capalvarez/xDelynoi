#ifndef XDELYNOI_XINDEXSEGMENT_H
#define XDELYNOI_XINDEXSEGMENT_H

#include <delynoi/models/basic/IndexSegment.h>

class xIndexSegment: public IndexSegment {
public:
    xIndexSegment(int i1, int i2);
    bool isSegmentInBoundary(std::vector<Point> points);
};

#endif