#include <xDelynoi/operations/MeshRefiner.h>

MeshRefiner::MeshRefiner(xMesh *mesh, ElementConstructor *constructor) {
    this->mesh = mesh;
    this->constructor = constructor;
}

void MeshRefiner::refine(xPolygon *elem, std::vector<Point> pointsToAdd) {
    int elemIndex = utilities::indexOf(this->mesh->getPolygons(), elem);

    UniqueList<Point>& points = mesh->getPoints();
    auto pointMap = this->addPoints(points, pointsToAdd);

    SimpleMesh mesh = this->computeElements(elem, elemIndex, pointMap);

    RefineAdapter::includeNewElements(this->mesh, mesh, pointMap, elemIndex, this->constructor);
}

std::unordered_map<int,int> MeshRefiner::addPoints(UniqueList<Point>& points, std::vector<Point> pointsToAdd) {
    std::unordered_map<int,int> pointMap = RefineAdapter::includeNewPoints(points, pointsToAdd);

    return pointMap;
}
