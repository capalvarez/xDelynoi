#ifndef XDELYNOI_GEOMETRIC_OPS_H
#define XDELYNOI_GEOMETRIC_OPS_H

#include <vector>
#include <delynoi/models/basic/Point.h>

namespace geometric_ops{
    void fixCCW(std::vector<int>& pointList, int reference, std::vector<Point> points);
    bool isCCW(std::vector<int> pointList, int reference, std::vector<Point>& points);
}

#endif