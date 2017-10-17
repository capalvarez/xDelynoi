#include <xDelynoi/models/xMesh.h>
#include <delynoi/models/Region.h>
#include <delynoi/voronoi/TriangleVoronoiGenerator.h>

int main(){
    std::vector<Point> square_points = {Point(0,0), Point(10,0), Point(10,10), Point(0,10)};
    Region square(square_points);

    square.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 3, 3);
    std::vector<Point> seeds = square.getSeedPoints();
    TriangleVoronoiGenerator g(seeds, square);
    Mesh<Polygon> m = g.getMesh();

    xMesh destructable(m);
    destructable.printInFile("destructible.txt");

    destructable.swapPoints(destructable.getPoint(8), destructable.getPoint(3));

    destructable.printInFile("swapPoint8.txt");
}
