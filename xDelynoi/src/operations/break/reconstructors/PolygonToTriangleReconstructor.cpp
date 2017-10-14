#include <xDelynoi/operations/break/reconstructors/PolygonToTriangleReconstructor.h>

PolygonToTriangleReconstructor::PolygonToTriangleReconstructor(ElementConstructor *constructor) : ElementReconstructor(
        constructor) {}

std::vector<xPolygon *>
PolygonToTriangleReconstructor::reconstructElement(std::vector<int> points, UniqueList<Point> meshPoints) {
    std::vector<xPolygon*> polygons;

    if(points.size()==3){
        polygons.push_back(constructor->createNewElement(points, meshPoints));
    }else{

    }


    return polygons;
}
