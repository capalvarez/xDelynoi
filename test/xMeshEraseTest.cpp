#include <delynoi/models/Region.h>
#include <delynoi/voronoi/TriangleVoronoiGenerator.h>
#include <xDelynoi/models/xMesh.h>
#include <delynoi/models/hole/CircularHole.h>

void erasePoint(xMesh destructable);
void erasePolygon(xMesh destructable);
void erasePointInBorder(xMesh destructable);

int main(){
    std::vector<Point> square_points = {Point(0,0), Point(10,0), Point(10,10), Point(0,10)};
    Region square(square_points);
    Hole circular = CircularHole(Point(5,10), 2);
    square.addHole(circular);

    square.generateSeedPoints(PointGenerator(functions::random_double(0,10), functions::random_double(0,10)), 10, 10);
    std::vector<Point> seeds = square.getSeedPoints();
    TriangleVoronoiGenerator g(seeds, square);
    Mesh<Polygon> m = g.getMesh();

    xMesh destructable(m, Config(Configurations::config::PolygonalDefault));
    destructable.printInFile("destructible.txt");


    std::vector<int> indexes = {93,163,241,268};
    for (int i = 0; i < indexes.size(); ++i) {
        Point toErase = destructable.getPoint(indexes[i]);

        destructable.erase(toErase);
    }

    destructable.printInFile("erasedPoints.txt");

    Polygon toErase = destructable.getPolygon(44);
    destructable.erase(toErase);

    destructable.printInFile("erasePolygon.txt");
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

void erasePointInBorder(xMesh destructable){
    Point toErase = destructable.getPoint(24);
    destructable.erase(toErase);

    destructable.printInFile("erasePoint24.txt");
}