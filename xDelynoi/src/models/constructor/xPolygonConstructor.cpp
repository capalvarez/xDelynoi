#include <xDelynoi/models/constructor/xPolygonConstructor.h>

xPolygon *xPolygonConstructor::createNewElement(std::vector<int> points, UniqueList<Point> meshPoints) {
    return new xPolygon(Polygon(points, meshPoints.getList()));
}
