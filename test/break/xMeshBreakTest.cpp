#include <delynoi/models/basic/Point.h>
#include <delynoi/models/Region.h>
#include <delynoi/voronoi/TriangleVoronoiGenerator.h>
#include <xDelynoi/models/xMesh.h>

void breakStraightLine(xMesh mesh);
void breakDiagonalLine(xMesh mesh);
void breakThroughVertex(xMesh mesh);
void breakFromBoundary(xMesh mesh);
void breakFromBoundaryVertex(xMesh mesh);

int main(){
    std::vector<Point> unicorn_points = {Point(2,0), Point(3,0.5), Point(3.5,2), Point(4,4), Point(6,4), Point(8.5,4),
                                         Point(9,2), Point(9.5,0.5), Point(10,0), Point(10.5,0.5), Point(11.2,2.5),
                                         Point(11.5,4.5), Point(11.8,8.75), Point(11.8,11.5), Point(13.5,11), Point(14.5,11.2),
                                         Point(15,12), Point(15,13), Point(15,14.5), Point(14,16.5), Point(15,19.5), Point(15.2,20),
                                         Point(14.5,19.7), Point(11.8,18.2), Point(10.5,18.3), Point(10,18), Point(8,16),
                                         Point(7.3,15.3), Point(7,13.8), Point(6.7,11.5), Point(3.3,11.3), Point(1,10.5),
                                         Point(0.4,8.8), Point(0.3,6.8), Point(0.4,4), Point(0.8,2.1), Point(1.3,0.4)};
    Region unicorn(unicorn_points);

    unicorn.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 5, 5);
    std::vector<Point> seeds = unicorn.getSeedPoints();
    TriangleDelaunayGenerator g(unicorn, seeds);
    Mesh<Triangle> m = g.getConformingDelaunayTriangulation();

    xMesh destructable(m, Config(Configurations::config::ForceTriangulation));
    destructable.printInFile("destructible.txt");

    breakStraightLine(destructable);

}

void breakStraightLine(xMesh mesh){
    mesh.breakMesh({PointSegment(Point(7,6), Point(10,8)), PointSegment(Point(10,8), Point(6,7)), PointSegment(Point(6,7), Point(9,3))});

    mesh.printInFile("brokenSequenceLineTriangle.txt");
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
    mesh.breakMesh(PointSegment(Point(3.33333,3.33333), Point(8.33333,8.33333)));
    mesh.printInFile("brokenThroughVertex.txt");
}