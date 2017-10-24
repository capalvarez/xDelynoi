#include <delynoi/models/Region.h>
#include <delynoi/voronoi/TriangleVoronoiGenerator.h>
#include <xDelynoi/models/xMesh.h>

void erasePoint(xMesh destructable);
void erasePolygon(xMesh destructable);

int main(){
    std::vector<Point> square_points = {Point(0,0), Point(10,0), Point(10,10), Point(0,10)};
    Region square(square_points);

    square.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 5, 5);
    std::vector<Point> seeds = square.getSeedPoints();
    TriangleVoronoiGenerator g(seeds, square);
    Mesh<Polygon> m = g.getMesh();

    xMesh destructable(m, Config(Configurations::config::PolygonalDefault));
    destructable.printInFile("destructible.txt");

    erasePoint(destructable);
}

void erasePoint(xMesh destructable){
    Point toErase = destructable.getPoint(8);
    destructable.erase(toErase);

    destructable.printInFile("erasePoint8.txt");
}

void erasePolygon(xMesh destructable){
    Polygon toErase = destructable.getPolygon(3);
    destructable.erase(toErase);

    destructable.printInFile("erasePolygon8.txt");
}