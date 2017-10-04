#include <xDelynoi/models/constructor/xTriangleConstructor.h>
#include <xDelynoi/models/xTriangle.h>

xPolygon *xTriangleConstructor::createNewElement(std::vector<int> points, UniqueList<Point> meshPoints) {
    return new xTriangle(Triangle(points, meshPoints.getList()));
}
