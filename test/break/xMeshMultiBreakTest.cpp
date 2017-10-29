#include <xDelynoi/models/xMesh.h>

int main(){
    std::vector<Point> square_points = {Point(0,0), Point(10,0), Point(10,10), Point(0,10)};
    Region square(square_points);

    square.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 7, 7);
    std::vector<Point> seeds = square.getSeedPoints();
    TriangleVoronoiGenerator g(seeds, square);
    Mesh<Polygon> m = g.getMesh();

    xMesh destructable(m, Config(Configurations::config::PolygonalDefault));
    destructable.printInFile("destructible.txt");

    std::vector<PointSegment> segs = {PointSegment(Point(2,6), Point(5,6)), PointSegment(Point(5,6), Point(8,9))};

    destructable.breakMesh(segs);
    destructable.printInFile("brokenStraightLine.txt");
}

