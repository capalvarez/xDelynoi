#include <xDelynoi/models/xMesh.h>

void breakOnePolygonInside(xMesh mesh);
void breakOnePolygonVertices(xMesh mesh);
void breakOnePolygonSides(xMesh mesh);
void breakOnePolygonSegment(xMesh mesh);

int main(){
    std::vector<Point> square_points = {Point(0,0), Point(10,0), Point(10,10), Point(0,10)};
    Region square(square_points);

    square.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 8, 8);
    std::vector<Point> seeds = square.getSeedPoints();
    TriangleVoronoiGenerator g(seeds, square);
    Mesh<Polygon> m = g.getMesh();

    xMesh destructable(m, Config(Configurations::config::PolygonalEndWithTriangles));
    destructable.printInFile("destructible.txt");

    breakOnePolygonSides(destructable);
}

void breakOnePolygonInside(xMesh mesh){
    mesh.breakMesh(PointSegment(Point(2,6), Point(3,6)));
    mesh.printInFile("brokenStraightLine.txt");
}

void breakOnePolygonVertices(xMesh mesh){
    mesh.breakMesh(PointSegment(Point(3.57143,5), Point(5,6.42857)));
    mesh.printInFile("breakOnePolygonVertices.txt");
}

void breakOnePolygonSides(xMesh mesh){
    mesh.breakMesh(PointSegment(Point(3.57143,5.2), Point(5,5.2)));
    mesh.printInFile("breakOnePolygonSides.txt");
}

void breakOnePolygonSegment(xMesh mesh){
    mesh.breakMesh(PointSegment(Point(3.57143,5), Point(5,5)));
    mesh.printInFile("breakOnePolygonSegment.txt");
}
