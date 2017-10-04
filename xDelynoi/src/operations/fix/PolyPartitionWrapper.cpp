#include <xDelynoi/operations/fix/PolyPartitionWrapper.h>

PolyPartitionWrapper::PolyPartitionWrapper(xMesh *mesh, ElementConstructor *constructor) {
    this->mesh = mesh;
    this->constructor = constructor;
}

std::vector<xPolygon *> PolyPartitionWrapper::partition(xPolygon *elem) {
    TPPLPartition partition;
    std::list<TPPLPoly> result;

    TPPLPoly poly;

    std::vector<Point> points = elem->getPoints(mesh->getPoints());

    poly.Init(elem->numberOfSides());

    for (int i = 0; i < elem->numberOfSides(); ++i) {
        poly[i].x = points[i].getX();
        poly[i].y = points[i].getY();
    }

    partition.ConvexPartition_HM(&poly, &result);

    UniqueList<Point> partitionPoints;

    for (auto iter = result.begin(); iter != result.end(); ++iter) {
        for (int j = 0; j < iter->GetNumPoints(); ++j) {
            int index = partitionPoints.push_back();
        }
    }
}
