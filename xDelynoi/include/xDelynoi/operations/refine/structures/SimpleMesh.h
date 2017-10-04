#ifndef XDELYNOI_SIMPLEMESH_H
#define XDELYNOI_SIMPLEMESH_H

#include <vector>
#include <delynoi/models/basic/Point.h>
#include <utilities/UniqueList.h>

template <class T>
class SimpleMesh{
private:
    std::vector<T> elements;
    UniqueList<Point> points;
public:
    SimpleMesh();
    SimpleMesh(std::vector<T> elems, UniqueList<Point> points);

    std::vector<T> getElements();
    std::vector<Point> getPoints();
};

#endif