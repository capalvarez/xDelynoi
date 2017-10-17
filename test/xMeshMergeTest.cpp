#include <xDelynoi/models/xMesh.h>
#include <delynoi/voronoi/TriangleVoronoiGenerator.h>

void twoElementMerge(xMesh mesh);
void multipleElementMerge(xMesh mesh);

int main(){
    std::vector<Point> square_points = {Point(0,0), Point(10,0), Point(10,10), Point(0,10)};
    Region square(square_points);

    square.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 5, 5);
    std::vector<Point> seeds = square.getSeedPoints();
    TriangleVoronoiGenerator g(seeds, square);
    Mesh<Polygon> m = g.getMesh();

    xMesh destructable(m);
    destructable.printInFile("destructible.txt");

    multipleElementMerge(destructable);
}

void twoElementMerge(xMesh mesh){
    mesh.mergeElements(7,11);
    mesh.printInFile("merged711.txt");
    mesh.getSegments()->printInFile("merged711_neigh.txt");
    mesh.mergeElements(7,13);
    mesh.printInFile("merged713.txt");
}

void multipleElementMerge(xMesh mesh){
    std::vector<int> toMerge = {12,3,5,17};
    mesh.mergeElements(toMerge);

    mesh.printInFile("merged4.txt");
}