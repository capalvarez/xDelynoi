#ifndef XDELYNOI_XMESHELEMENTS_H
#define XDELYNOI_XMESHELEMENTS_H

#include <xDelynoi/models/neighbourhood/xPointMap.h>
#include <xDelynoi/models/xPolygon.h>

struct xMeshElements {
    UniqueList<Point> points ;
    std::vector<xPolygon> polygons;
    xSegmentMap *segments;
    xPointMap *pointMap;

    xMeshElements(UniqueList<Point> &p, std::vector<xPolygon> &poly, xSegmentMap *seg, xPointMap *pM){
        points = p;
        polygons = poly;
        segments = seg;
        pointMap = pM;
    }

    xMeshElements(){}
};

#endif