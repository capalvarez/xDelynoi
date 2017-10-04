#include <xDelynoi/operations/refine/VoronoiRefiner.h>

VoronoiRefiner::VoronoiRefiner(xMesh *mesh, ElementConstructor *constructor) : MeshRefiner(mesh, constructor) {}

SimpleMesh VoronoiRefiner::computeElements(xPolygon *elem, std::vector<Point> toAdd,
                                           std::unordered_map<int, int>& pointMap) {
    UniqueList<Point>& points = this->mesh->getPoints();

    Region region(*elem, points.getList());
    TriangleVoronoiGenerator voronoiGenerator(toAdd, region);
    Mesh<Polygon> voronoi = voronoiGenerator.getMesh();

    pointMap = RefineAdapter::includeNewPoints(points, voronoi.getPoints().getList());

    SimpleMesh toReturn (voronoi.getPolygons(), voronoi.getPoints());

    return toReturn;
}

std::unordered_map<int, int> VoronoiRefiner::addPoints(UniqueList<Point> &points, std::vector<Point> pointsToAdd) {
    return std::unordered_map<int,int>();
}
