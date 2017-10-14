#include <xDelynoi/operations/fix/PolyPartitionWrapper.h>

PolyPartitionWrapper::PolyPartitionWrapper(xMesh *mesh, ElementConstructor *constructor) {
    this->mesh = mesh;
    this->constructor = constructor;
}

SimpleMesh PolyPartitionWrapper::partition(xPolygon *elem) {
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
    std::vector<xPolygon*> partitionPolygons;

    for (auto iter = result.begin(); iter != result.end(); ++iter) {
        std::vector<int> polyPoints;

        for (int j = 0; j < iter->GetNumPoints(); ++j) {
            int index = partitionPoints.push_back(Point(iter->GetPoint(j).x, iter->GetPoint(j).y));

            polyPoints.push_back(index);
        }

        partitionPolygons.push_back(constructor->createNewElement(polyPoints, partitionPoints));
    }

    return SimpleMesh(partitionPolygons, partitionPoints);
}
