#ifndef XDELYNOI_SIMPLEMESH_H
#define XDELYNOI_SIMPLEMESH_H

#include <vector>
#include <delynoi/models/basic/Point.h>
#include <utilities/UniqueList.h>
#include <xDelynoi/models/xPolygon.h>
#include <delynoi/models/polygon/Triangle.h>

class SimpleMesh{
private:
    std::vector<Polygon> elements;
    UniqueList<Point> points;
public:
    SimpleMesh();
    SimpleMesh(std::vector<Polygon> elems, UniqueList<Point> points);
    SimpleMesh(std::vector<Triangle> elems, UniqueList<Point> points);

    std::vector<Polygon> getElements();
    std::vector<Point> getPoints();
};

#endif