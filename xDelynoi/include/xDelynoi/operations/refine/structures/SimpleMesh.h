#ifndef XDELYNOI_SIMPLEMESH_H
#define XDELYNOI_SIMPLEMESH_H

#include <vector>
#include <delynoi/models/basic/Point.h>
#include <utilities/UniqueList.h>
#include <xDelynoi/models/xPolygon.h>

class SimpleMesh{
private:
    std::vector<xPolygon*> elements;
    UniqueList<Point> points;
public:
    SimpleMesh();
    SimpleMesh(std::vector<xPolygon*> elems, UniqueList<Point> points);

    std::vector<xPolygon*> getElements();
    std::vector<Point> getPoints();
};

#endif