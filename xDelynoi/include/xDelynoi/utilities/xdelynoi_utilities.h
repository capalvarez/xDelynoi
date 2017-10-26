#ifndef XDELYNOI_XDELYNOI_UTILITIES_H
#define XDELYNOI_XDELYNOI_UTILITIES_H

#include <vector>
#include <delynoi/models/basic/IndexSegment.h>
#include <utilities/UniqueList.h>

namespace xdelynoi_utilities{
    extern IndexSegment convert(PointSegment s, UniqueList<Point> points);
    extern PointSegment convert(IndexSegment s, UniqueList<Point> points);
    extern void getAllPairs(std::vector<Pair<int>>& pairs, std::vector<int> numbers);
}

#endif