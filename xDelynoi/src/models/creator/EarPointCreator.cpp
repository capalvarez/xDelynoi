#include <xDelynoi/models/creator/EarPointCreator.h>
#include <delynoi/triangulation/EarTriangulationGenerator.h>

std::vector<Point> EarPointCreator::createPoints(xPolygon poly, UniqueList<Point> points) {
    std::vector<Point> generatedPoints;

    EarTriangulationGenerator generator;
    std::vector<Triangle> triangles = generator.triangulate(poly, points.getList());

    for (Triangle t: triangles) {
        Point candidate = t.getCentroid();

        if(poly.containsPoint(points.getList(), candidate)){
            generatedPoints.push_back(candidate);
        }
    }

    return generatedPoints;
}
