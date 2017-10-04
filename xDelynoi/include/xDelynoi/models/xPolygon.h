#ifndef XDELYNOI_XPOLYGON_H
#define XDELYNOI_XPOLYGON_H

#include <delynoi/models/polygon/Polygon.h>
#include <xDelynoi/models/neighbourhood/xSegmentMap.h>

class xPolygon: public Polygon {
private:
    Pair<int> segmentNotContained(std::vector<IndexSegment> s);
public:
    xPolygon(Polygon polygon);
    Pair<int> commonEdgesBorderPoints(xPolygon other, std::vector<Point> points, bool& pacman_case);
    bool isVertex(Point p, std::vector<Point> points, int &vertexIndex);
    bool isVertex(Point p, std::vector<Point> points);
    bool isVertex(int index);
    std::vector<IndexSegment> getAdjacentEdges(int i);
    void replaceVertex(int oldVertex, int newVertex, xSegmentMap& edges);

    void replaceSegment(IndexSegment seg, std::vector<IndexSegment> segs, std::vector<Point> points);
};

#endif