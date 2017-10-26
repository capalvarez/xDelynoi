#ifndef XDELYNOI_XPOLYGON_H
#define XDELYNOI_XPOLYGON_H

#include <delynoi/models/polygon/Polygon.h>
#include <xDelynoi/models/neighbourhood/xSegmentMap.h>

class xPolygon: public Polygon {
private:
    Pair<int> segmentNotContained(std::vector<IndexSegment> s);
    std::vector<IndexSegment> surroundingVertices(int vertexIndex);
public:
    xPolygon(Polygon polygon);
    xPolygon(std::vector<int> points, UniqueList<Point> meshPoints);
    xPolygon(std::vector<int> points, std::vector<Point> meshPoints);
    Pair<int> commonEdgesBorderPoints(xPolygon other, std::vector<Point> points, bool& pacman_case);
    bool isVertex(Point p, std::vector<Point> points, int &vertexIndex);
    bool isVertex(Point p, std::vector<Point> points);
    bool isVertex(int index);
    std::vector<IndexSegment> getAdjacentEdges(int i);
    void replaceVertex(int oldVertex, int newVertex, xSegmentMap* edges);

    void replaceSegment(IndexSegment seg, std::vector<IndexSegment> segs, std::vector<Point> points);
    int numberOfInteresectedSegments(PointSegment direction, std::vector<Point> points);

    void insertOnSegment(IndexSegment segment, int point);
    void insertOnSegment(IndexSegment segment, std::vector<int> point);
    IndexSegment getOtherContainer(IndexSegment segment, int vertexIndex);
};

#endif