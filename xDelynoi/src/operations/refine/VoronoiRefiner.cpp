#include <xDelynoi/operations/refine/VoronoiRefiner.h>

VoronoiRefiner::VoronoiRefiner(xMesh *mesh, ElementConstructor *constructor) : MeshRefiner(mesh, constructor) {}

SimpleMesh VoronoiRefiner::computeElements(xPolygon *elem, std::vector<Point> toAdd) {
    UniqueList<Point>& points = this->mesh->getPoints();

    Region region(*elem, points.getList());
    TriangleVoronoiGenerator voronoiGenerator(toAdd, region);
    Mesh<Polygon> voronoi = voronoiGenerator.getMesh();

    SimpleMesh toReturn (voronoi.getPolygons(), voronoi.getPoints());

    return toReturn;
}

