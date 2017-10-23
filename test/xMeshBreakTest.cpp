#include <delynoi/models/basic/Point.h>
#include <delynoi/models/Region.h>
#include <delynoi/voronoi/TriangleVoronoiGenerator.h>
#include <xDelynoi/models/xMesh.h>

void breakStraightLine(xMesh mesh);
void breakDiagonalLine(xMesh mesh);
void breakThroughVertex(xMesh mesh);
void breakFromBoundary(xMesh mesh);
void breakThroughSegment(xMesh mesh);

int main(){
    std::vector<Point> square_points = {Point(0,0), Point(10,0), Point(10,10), Point(0,10)};
    Region square(square_points);

    square.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 3, 3);
    std::vector<Point> seeds = square.getSeedPoints();
    TriangleVoronoiGenerator g(seeds, square);
    Mesh<Polygon> m = g.getMesh();

    xMesh destructable(m);
    destructable.printInFile("destructible.txt");
}

void breakStraightLine(xMesh mesh){
    mesh.breakMesh(PointSegment(Point(2,5), Point(8,5)));
    mesh.printInFile("brokenStraightLine.txt");
}