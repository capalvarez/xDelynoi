#include <xDelynoi/operations/refine/VoronoiRefiner.h>

VoronoiRefiner::VoronoiRefiner() {}

SimpleMesh VoronoiRefiner::computeElements(xPolygon elem, std::vector<Point> toAdd) {
    UniqueList<Point>* points = this->mesh->points;

    Region region(elem, points->getList());
    TriangleVoronoiGenerator voronoiGenerator(toAdd, region);
    Mesh<Polygon> voronoi = voronoiGenerator.getMesh();

    SimpleMesh toReturn (voronoi.getPolygons(), voronoi.getPoints());

    return toReturn;
}

MeshOperator *VoronoiRefiner::clone() {
    return new VoronoiRefiner;
}
