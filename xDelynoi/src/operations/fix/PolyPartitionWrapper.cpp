#include <xDelynoi/operations/fix/PolyPartitionWrapper.h>

PolyPartitionWrapper::PolyPartitionWrapper(xMeshElements* mesh) {
    this->mesh = mesh;
}

SimpleMesh PolyPartitionWrapper::partition(xPolygon elem) {
    TPPLPartition partition;
    std::list<TPPLPoly> result;

    TPPLPoly poly;

    std::vector<Point> points = elem.getPoints(mesh->points->getList());

    poly.Init(elem.numberOfSides());

    for (int i = 0; i < elem.numberOfSides(); ++i) {
        poly[i].x = points[i].getX();
        poly[i].y = points[i].getY();
    }

    partition.ConvexPartition_HM(&poly, &result);

    UniqueList<Point> partitionPoints;
    std::vector<Polygon> partitionPolygons;

    for (auto iter = result.begin(); iter != result.end(); ++iter) {
        std::vector<int> polyPoints;

        for (int j = 0; j < iter->GetNumPoints(); ++j) {
            Point newPoint(iter->GetPoint(j).x, iter->GetPoint(j).y);
            int index = partitionPoints.push_back(newPoint);

            polyPoints.push_back(index);
        }

        partitionPolygons.push_back(Polygon(polyPoints, partitionPoints.getList()));
    }

    return SimpleMesh(partitionPolygons, partitionPoints);
}
