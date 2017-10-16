#include <xDelynoi/operations/break/reconstructors/PolygonToTriangleReconstructor.h>
#include <delynoi/models/polygon/Triangle.h>
#include <delynoi/triangulation/EarTriangulationGenerator.h>

std::vector<xPolygon>
PolygonToTriangleReconstructor::reconstructElement(std::vector<int> points, UniqueList<Point> meshPoints) {
    std::vector<xPolygon> polygons;

    EarTriangulationGenerator generator;
    Polygon p(points, meshPoints.getList());
    std::vector<Triangle> triangulation = generator.triangulate(p, meshPoints.getList());

    for (Triangle t : triangulation){
        polygons.push_back(xPolygon(t.getPoints(), meshPoints));
    }

    return polygons;
}
