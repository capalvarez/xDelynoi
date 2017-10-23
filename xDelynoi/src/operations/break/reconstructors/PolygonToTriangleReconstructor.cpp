#include <xDelynoi/operations/break/reconstructors/PolygonToTriangleReconstructor.h>
#include <delynoi/models/polygon/Triangle.h>
#include <delynoi/triangulation/EarTriangulationGenerator.h>

std::vector<xPolygon>
PolygonToTriangleReconstructor::reconstructElement(std::vector<int> points, std::vector<Point> meshPoints) {
    std::vector<xPolygon> polygons;

    EarTriangulationGenerator generator;
    Polygon p(points, meshPoints);
    std::vector<Triangle> triangulation = generator.triangulate(p, meshPoints);

    for (Triangle t : triangulation){
        polygons.push_back(xPolygon(t.getPoints(), meshPoints));
    }

    return polygons;
}
