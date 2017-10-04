#ifndef XDELYNOI_XPOINTMAP_H
#define XDELYNOI_XPOINTMAP_H

#include <delynoi/models/neighbourhood/PointMap.h>

class xPointMap : public PointMap{
public:
    xPointMap();
    xPointMap(PointMap pointMap);
    void changeNeighbour(Point p, int oldNeighbour, int newNeighbour);
    void deleteElement(Point p);
    std::vector<int> getAllNeighbours(std::vector<Point> points, int poly_index);
};

#endif