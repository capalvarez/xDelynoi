#include <xDelynoi/models/creator/DelaunayPointCreator.h>
#include <delynoi/triangulation/DelaunayTriangulationGenerator.h>

std::vector<Point> DelaunayPointCreator::createPoints(xPolygon poly, UniqueList<Point> points) {
    std::vector<Point> generatedPoints;

    DelaunayTriangulationGenerator generator;
    std::vector<Triangle> triangles = generator.triangulate(poly, points.getList());

    for (Triangle t: triangles) {
        Point candidate = t.getCircumcenter();

        if(poly.containsPoint(points.getList(), candidate)){
            generatedPoints.push_back(candidate);
        }
    }

    return generatedPoints;
}
