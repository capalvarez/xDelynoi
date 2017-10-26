#include <xDelynoi/operations/break/functions/break_functions.h>

namespace break_functions{
    void partitionPolygonFromSegment(xMeshElements* mesh, ElementReconstructor* constructor, NeighbourInfo n1, NeighbourInfo& n2, xPolygon poly1, std::vector<int>& new1,
                                     std::vector<int>& new2, int p1, int p2, int init){
        UniqueList<Point> points = *mesh->points;
        xSegmentMap* edges = mesh->segments;
        xPointMap* pointMap = mesh->pointMap;
        std::vector<xPolygon>* polygons = mesh->polygons;

        UniqueList<int> newPoints;
        std::vector<int> newElements = break_functions::computeNewPolygons(mesh, constructor, n1, n2, poly1, new1, new2, p1, p2);

        if(init>=0){
            polygons->at(init).insertOnSegment(n1.edge, p1);
        }

        polygons->at(n2.neighbour).insertOnSegment(n2.edge, p2);

        // Get the edge information for the old polygon and update it
        if(!n1.isVertex){
            edges->deleteElement(n1.edge);
        }
        if(!n2.isVertex){
            edges->deleteElement(n2.edge);
        }

        edges->insert(IndexSegment(p1,p2),NeighboursBySegment(n1.neighbour,n1.neighbour));
        pointMap->insert(points[p1], {init, n1.neighbour, n1.neighbour});
        pointMap->insert(points[p2], {n2.neighbour, n1.neighbour, n1.neighbour});

        for(int newElem: newElements){
            xPolygon elem = polygons->at(newElem);
            std::vector<IndexSegment> segments;
            elem.getSegments(segments);
            std::vector<int> elemPoints = elem.getPoints();

            for (IndexSegment s: segments) {
                edges->replaceNeighbour(s, n1.neighbour, newElem);
            }

            for (int j = 0; j < elemPoints.size(); ++j) {
                pointMap->replaceNeighbour(points[elemPoints[j]], n1.neighbour, newElem);
            }
        }

        if(!n1.isVertex){
            edges->insert_if_null(IndexSegment(p1,n1.edge.getFirst()),init);
            edges->insert_if_null(IndexSegment(p1,n1.edge.getSecond()), init);
        }

        if(!n2.isVertex){
            edges->insert_if_null(IndexSegment(p2,n2.edge.getFirst()), n2.neighbour);
            edges->insert_if_null(IndexSegment(p2,n2.edge.getSecond()), n2.neighbour);
        }

        n2.extraPoint = p2;
    }

    std::vector<int> computeNewPolygons(xMeshElements* mesh, ElementReconstructor* constructor, NeighbourInfo n1, NeighbourInfo &n2,
                                        xPolygon poly1, std::vector<int> &new1, std::vector<int> &new2, int p1, int p2) {
        UniqueList<Point>* points = mesh->points;
        std::vector<xPolygon>* polygons = mesh->polygons;

        std::vector<int> poly1_points = poly1.getPoints();

        n1.orderCCW(points->getList(), poly1.getCentroid());
        n2.orderCCW(points->getList(), poly1.getCentroid());

        int indexOfStart, point;

        if (delynoi_utilities::orientation(points->operator[](p1), points->operator[](p2), points->operator[](n2.edge.getFirst())) > 0) {
            indexOfStart = utilities::indexOf(poly1_points, n2.edge.getFirst());
            point = n2.edge.getFirst();
        } else {
            indexOfStart = utilities::indexOf(poly1_points, n2.edge.getSecond());
            point = n2.edge.getSecond();
        }

        bool edgePointsPassed = false;

        while (true) {
            if (n1.isVertex) {
                if (point == p1) {
                    break;
                }
            } else {
                if (point == n1.edge.getFirst() || point == n1.edge.getSecond() || point == n1.extraPoint) {
                    if (edgePointsPassed) {
                        break;
                    } else {
                        edgePointsPassed = true;
                    }
                }
            }

            if (point != p1 && point != p2) {
                new1.push_back(point);
            }

            point = poly1_points[(indexOfStart + 1) % poly1_points.size()];

            indexOfStart++;
        }

        edgePointsPassed = false;

        while (true) {
            if (n2.isVertex) {
                if (point == p2) {
                    break;
                }
            } else {
                if (point == n2.edge.getFirst() || point == n2.edge.getSecond()) {
                    if (edgePointsPassed) {
                        break;
                    } else {
                        edgePointsPassed = true;
                    }
                }
            }

            if (point != p1 && point != p2) {
                new2.push_back(point);
            }

            point = poly1_points[(indexOfStart + 1) % poly1_points.size()];

            indexOfStart++;
        }

        std::vector<xPolygon> newPolygons1 = constructor->reconstructElement(new1, points->getList());
        std::vector<xPolygon> newPolygons2 = constructor->reconstructElement(new2, points->getList());

        newPolygons1.insert(newPolygons1.end(), newPolygons2.begin(), newPolygons2.end());

        std::vector<int> newIndexes;
        newIndexes.push_back(n1.neighbour);
        polygons->operator[](n1.neighbour) = newPolygons1[0];

        for (int i = 1; i < newPolygons1.size(); ++i) {
            polygons->push_back(newPolygons1[i]);
            newIndexes.push_back(polygons->size() - 1);
        }

        return newIndexes;
    }
}