#include <xDelynoi/operations/MeshRefiner.h>

MeshRefiner::MeshRefiner(xMesh *mesh) {
    this->mesh = mesh;
}

void MeshRefiner::refine(xPolygon elem, std::vector<Point> pointsToAdd) {
    int elemIndex = utilities::indexOf(this->mesh->getPolygons(), elem);
    UniqueList<Point>& points = mesh->getPoints();

    SimpleMesh mesh = this->computeElements(elem, pointsToAdd);
    std::unordered_map<int,int> pointMap = AddElementsAdapter::includeNewPoints(points, mesh.getPoints());

    AddElementsAdapter::includeNewElements(this->mesh, mesh, pointMap, elemIndex);
}
