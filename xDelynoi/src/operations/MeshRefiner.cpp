#include <xDelynoi/operations/MeshRefiner.h>

MeshRefiner::MeshRefiner() {}

void MeshRefiner::refine(xPolygon elem, std::vector<Point> pointsToAdd) {
    int elemIndex = utilities::indexOf(*this->mesh->polygons, elem);
    UniqueList<Point>* points = mesh->points;

    SimpleMesh mesh = this->computeElements(elem, pointsToAdd);
    std::unordered_map<int,int> pointMap = AddElementsAdapter::includeNewPoints(*points, mesh.getPoints());

    AddElementsAdapter::includeNewElements(this->mesh, mesh, pointMap, elemIndex);
}
