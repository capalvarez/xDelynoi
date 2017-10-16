#include <xDelynoi/models/constructor/xTriangleConstructor.h>
#include <xDelynoi/models/xTriangle.h>

xPolygon *xTriangleConstructor::createNewElement(std::vector<int> points, UniqueList<Point> meshPoints) {
    xPolygon *newTriangle = new xTriangle(Triangle(points, meshPoints.getList()));

    return newTriangle;
}
