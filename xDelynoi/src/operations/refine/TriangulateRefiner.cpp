#include <xDelynoi/operations/refine/TriangulateRefiner.h>

TriangulateRefiner::TriangulateRefiner(){}

SimpleMesh TriangulateRefiner::computeElements(xPolygon elem, std::vector<Point> toAdd) {
    UniqueList<Point> points = *this->mesh->points;

    Region r (elem, points.getList());
    TriangleDelaunayGenerator generator(r, toAdd);
    Mesh<Triangle> triangulation = generator.getConstrainedDelaunayTriangulation();

    SimpleMesh meshToInclude(triangulation.getPolygons(), triangulation.getPoints());

    return meshToInclude;
}

MeshOperator *TriangulateRefiner::clone() {
    return new TriangulateRefiner;
}
