#ifndef XDELYNOI_NEIGHBOURINFO_H
#define XDELYNOI_NEIGHBOURINFO_H

#include <delynoi/models/basic/Point.h>
#include <delynoi/models/basic/IndexSegment.h>

struct NeighbourInfo{
    int neighbour;
    Point intersection;
    IndexSegment edge;
    bool isEdge = false;
    bool isVertex = false;
    int extraPoint;

    NeighbourInfo(){}

    NeighbourInfo(int n, IndexSegment e, Point i, bool is){
        neighbour = n;
        edge = e;
        intersection = i;
        isEdge = is;
    }

    NeighbourInfo(int n, IndexSegment e, Point i){
        neighbour = n;
        edge = e;
        intersection = i;
    }

    void orderCCW(std::vector<Point> points, Point center){
        edge.orderCCW(points, center);
    }
};

#endif