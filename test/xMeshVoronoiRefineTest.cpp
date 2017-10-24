#include <delynoi/models/basic/Point.h>
#include <delynoi/models/Region.h>
#include <delynoi/voronoi/TriangleVoronoiGenerator.h>
#include <xDelynoi/models/xMesh.h>
#include <xDelynoi/models/creator/CentroidPointCreator.h>

void refineWithPoint(xMesh mesh) {
    mesh.refine(Point(5,5));
    mesh.printInFile("refinedWithPoint.txt");
}

void refineWithPointCreator(xMesh mesh) {
    mesh.refine(mesh.getPolygon(3), new CentroidPointCreator);
    mesh.printInFile("refinedWithCreator.txt");
}

void refineWithPointGenerator(xMesh mesh) {
    mesh.refine(mesh.getPolygon(6), PointGenerator(functions::constant(), functions::constant()), 2, 2);
    mesh.printInFile("refinedWithGenerator.txt");
}

int main(){
    std::vector<Point> square_points = {Point(0,0), Point(10,0), Point(10,10), Point(0,10)};
    Region square(square_points);

    square.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 3, 3);
    std::vector<Point> seeds = square.getSeedPoints();
    TriangleVoronoiGenerator g(seeds, square);
    Mesh<Polygon> m = g.getMesh();

    xMesh destructable(m, Config(Configurations::config::PolygonalDefault));
    destructable.printInFile("destructible.txt");

    refineWithPointGenerator(destructable);
}

