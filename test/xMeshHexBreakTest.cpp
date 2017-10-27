#include <delynoi/models/basic/Point.h>
#include <delynoi/models/Region.h>
#include <delynoi/voronoi/TriangleVoronoiGenerator.h>
#include <xDelynoi/models/xMesh.h>

void breakStraightLine(xMesh mesh);
void breakDiagonalLine(xMesh mesh);
void breakThroughVertex(xMesh mesh);
void breakFromBoundary(xMesh mesh);
void breakFromBoundaryVertex(xMesh mesh);
void breakThroughSegment(xMesh mesh);
void breakMeshRightToLeft(xMesh mesh);

int main(){
    std::vector<Point> square_points = {Point(0,0), Point(10,0), Point(10,10), Point(0,10)};
    Region square(square_points);

    square.generateSeedPoints(PointGenerator(functions::constant(), functions::displace_points(1.25)), 8, 8);
    std::vector<Point> seeds = square.getSeedPoints();
    TriangleVoronoiGenerator g(seeds, square);
    Mesh<Polygon> m = g.getMesh();

    xMesh destructable(m, Config(Configurations::config::PolygonalDefault));
    destructable.printInFile("destructible.txt");

    breakThroughVertex(destructable);

}

void breakStraightLine(xMesh mesh){
    mesh.breakMesh(PointSegment(Point(2,6), Point(6,6)));
    mesh.printInFile("brokenStraightLine.txt");
}

void breakDiagonalLine(xMesh mesh){
    mesh.breakMesh(PointSegment(Point(2,4), Point(6,8)));
    mesh.printInFile("brokenDiagonalLine.txt");
}

void breakFromBoundary(xMesh mesh){
    mesh.breakMesh(PointSegment(Point(0,1), Point(4,6)));
    mesh.printInFile("brokenFromBoundary.txt");
}

void breakFromBoundaryVertex(xMesh mesh){
    mesh.breakMesh(PointSegment(Point(0,5), Point(4,6)));
    mesh.printInFile("brokenFromVertexBoundary.txt");
}

void breakThroughVertex(xMesh mesh){
    mesh.breakMesh(PointSegment(Point(4.17578, 4.196), Point(7.25279,4.19643)));
    mesh.printInFile("brokenThroughVertex.txt");
}