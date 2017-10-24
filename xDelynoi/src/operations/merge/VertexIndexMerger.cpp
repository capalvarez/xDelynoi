#include <xDelynoi/operations/merge/VertexIndexMerger.h>

VertexIndexMerger::VertexIndexMerger() {}

bool VertexIndexMerger::areMergeable(xPolygon poly1, int poly2) {
    xSegmentMap* edges = mesh->segments;

    xPolygon p2 = mesh->polygons->at(poly2);

    std::vector<IndexSegment> poly1_segments;
    poly1.getSegments(poly1_segments);

    bool last_was_neighbour = edges->isNeighbour(poly1_segments.back(), poly2);
    bool exited_once = false;

    for(IndexSegment s: poly1_segments){
        bool areNeighbours = edges->isNeighbour(s, poly2);

        if(last_was_neighbour && !areNeighbours){
            if(!exited_once){
                exited_once = true;
            } else {
                return false;
            }
        }

        if(!last_was_neighbour && !areNeighbours && p2.isVertex(s.getFirst())){
            return false;
        }

        last_was_neighbour = areNeighbours;
    }

    return exited_once || last_was_neighbour;
}

std::vector<int> VertexIndexMerger::merge(xPolygon e1, xPolygon e2, Pair<int> endPoints, bool special_case) {
    if(e1==e2){
        return e1.getPoints();
    }

    std::vector<int> mergedPolygon;
    std::vector<int>& poly1_points = e1.getPoints();
    std::vector<int>& poly2_points = e2.getPoints();

    if(special_case) {
        for (int index: poly2_points){
            if(index==endPoints.first || index==endPoints.second)
                continue;

            poly1_points.erase(std::remove(poly1_points.begin(), poly1_points.end(), index), poly1_points.end());
        }

        return poly1_points;
    }

    int firstPointIndex_p1 = utilities::indexOf(poly1_points, endPoints.first);
    int secondPointIndex_p1 = utilities::indexOf(poly1_points, endPoints.second);
    int first_1, second_1, first_2, second_2;

    if(firstPointIndex_p1<secondPointIndex_p1) {
        first_1 = firstPointIndex_p1;
        second_1 = secondPointIndex_p1;
    } else{
        first_1 = secondPointIndex_p1;
        second_1 = firstPointIndex_p1;
    }

    if(!e2.isVertex(poly1_points[(first_1+1)%e1.numberOfSides()])) {
        int tmp = first_1;
        first_1 = second_1;
        second_1 = tmp;
    }

    int firstPointIndex_p2 = utilities::indexOf(poly2_points, endPoints.first);
    int secondPointIndex_p2 = utilities::indexOf(poly2_points, endPoints.second);

    if(firstPointIndex_p2<secondPointIndex_p2) {
        first_2 = firstPointIndex_p2;
        second_2 = secondPointIndex_p2;
    } else{
        first_2 = secondPointIndex_p2;
        second_2 = firstPointIndex_p2;
    }

    if(!e1.isVertex(poly2_points[(first_2+1)%e2.numberOfSides()])) {
        int tmp = first_2;
        first_2 = second_2;
        second_2 = tmp;
    }

    int i = (second_1 + 1)%e1.numberOfSides();
    while(i!=first_1){
        mergedPolygon.push_back(poly1_points[i]);

        i = (i+1)%e1.numberOfSides();
    }

    i = second_2;
    while(i!=first_2){
        mergedPolygon.push_back(poly2_points[i]);

        i = (i+1)%e2.numberOfSides();
    }

    mergedPolygon.push_back(poly2_points[first_2]);

    return mergedPolygon;
}

std::vector<int> VertexIndexMerger::mergeElements(xPolygon e1, xPolygon e2) {
    bool pacman_case = false;
    UniqueList<Point> points = *mesh->points;
    Pair<int> endPoints = e1.commonEdgesBorderPoints(e2, points.getList(), pacman_case);

    return merge(e1, e2, endPoints, pacman_case);
}

std::vector<int> VertexIndexMerger::mergeElements(xPolygon e1, xPolygon e2, IndexSegment endPoints) {
    Pair<int> points = Pair<int>(endPoints.getFirst(), endPoints.getSecond());

    return merge(e1, e2, points, false);
}

std::vector<int> VertexIndexMerger::mergeElements(std::vector<int> elements) {
    if(elements.size()==1){
        return mesh->polygons->at(elements[0]).getPoints();
    }

    std::vector<int> mergedPolygon;
    UniqueList<Point> pointsList = *mesh->points;
    std::vector<Point> points = pointsList.getList();
    int i = elements.size()-1;
    int j = elements.size()-2;

    while(true){
        if(j<0){
            throw std::invalid_argument("Impossible to merge polygons");
        }

        if(areMergeable(mesh->polygons->at(elements[i]), elements[j])){
            mergedPolygon = this->mergeElements(mesh->polygons->at(elements[i]), mesh->polygons->at(elements[j]));
            elements.erase(elements.begin()+i);
            elements.erase(elements.begin()+j);
            break;
        }else{
            j--;
        }
    }

    j = elements.size()-1;

    while(elements.size()!=0){
        xPolygon merged (Polygon(mergedPolygon, points));
        while(j>=0 && !areMergeable(merged, elements[j])){
            if(j==0){
                throw std::invalid_argument("Impossible to merge polygons");
            }
            j--;
        }

        if(merged.containsPoint(mesh->points->getList(), mesh->polygons->at(elements[j]).getCentroid())){
            elements.erase(elements.begin()+j);
            j = elements.size()-1;
            continue;
        }

        mergedPolygon = this->mergeElements(merged, mesh->polygons->at(elements[j]));
        elements.erase(elements.begin()+j);
        j = elements.size()-1;
    }

    return mergedPolygon;
}
