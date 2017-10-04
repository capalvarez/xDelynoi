#include <xDelynoi/operations/refine/TriangulateRefiner.h>


TriangulateRefiner::TriangulateRefiner(xMesh *mesh, ElementConstructor* constructor) : MeshRefiner(mesh, constructor){}

SimpleMesh TriangulateRefiner::computeElements(xPolygon *elem, std::vector<Point> toAdd, std::unordered_map<int, int>& pointMap) {
    UniqueList<Point>& points = this->mesh->getPoints();

    Region r (*elem, points.getList());
    TriangleDelaunayGenerator generator(r, toAdd);
    Mesh<Triangle> triangulation = generator.getConstrainedDelaunayTriangulation();

    SimpleMesh meshToInclude(triangulation.getPolygons(), triangulation.getPoints());

    return meshToInclude;
}
