#include <xDelynoi/operations/adapter/AddElementsAdapter.h>
#include <xDelynoi/models/basic/xIndexSegment.h>

std::unordered_map<int, int> AddElementsAdapter::includeNewPoints(UniqueList<Point> &meshPoints, std::vector<Point> points) {
    std::unordered_map<int,int> pointMap;

    for (int j = 0; j < points.size() ; ++j) {
        int pointIndex = meshPoints.push_back(points[j]);
        pointMap.insert(std::make_pair(j,pointIndex));
    }

    return pointMap;
}

void AddElementsAdapter::includeNewElements(xMesh *mesh, SimpleMesh toInclude, std::unordered_map<int, int> pointMap, int originalIndex) {
    std::unordered_map<int,std::unordered_map<IndexSegment,std::vector<IndexSegment>,SegmentHasher>> changesInNeighbours;

    UniqueList<Point>& meshPoints = mesh->getPoints();
    std::vector<xPolygon>& meshElements = mesh->getPolygons();
    SegmentMap& segments = mesh->getSegments();

    std::vector<Polygon> elements = toInclude.getElements();
    std::vector<Point> newPoints = toInclude.getPoints();

    std::vector<IndexSegment> containerSegments;
    mesh->getPolygon(originalIndex).getSegments(containerSegments);

    std::map<Angle,std::vector<IndexSegment>> containerSegmentsMap;

    for (IndexSegment s: containerSegments) {
        Angle angle = s.cartesianAngle(meshPoints.getList());

        std::vector<IndexSegment>& v = containerSegmentsMap[angle];
        v.push_back(s);
    }

    for (int i = 0; i < elements.size() ; ++i) {
        std::vector<int> oldPoints = elements[i].getPoints();
        int n = oldPoints.size();

        std::vector<int> newPolygonPoints;

        for (int k = 0; k < n ; ++k) {
            int newPoint = pointMap[oldPoints[k]];
            newPolygonPoints.push_back(newPoint);
        }

        xPolygon newPolygon(newPolygonPoints, meshPoints);
        int index;

        if(i<1){
            meshElements[originalIndex] = newPolygon;
            index = originalIndex;
        }else{
            meshElements.push_back(newPolygon);
            index = meshElements.size() - 1;
        }

        for (int j = 0; j < n; ++j) {
            bool changed = false;
            IndexSegment edge(newPolygonPoints[j], newPolygonPoints[(j+1)%n]);
            xIndexSegment originalEdge(oldPoints[j],oldPoints[(j+1)%n]);

            if(originalEdge.isSegmentInBoundary( newPoints)){
                Angle a = edge.cartesianAngle(meshPoints.getList());
                std::vector<IndexSegment> containerCandidates = containerSegmentsMap[a];

                for (int k = 0; k < containerCandidates.size(); ++k) {
                    if(containerCandidates[k].contains(meshPoints.getList(),edge)){
                        NeighboursBySegment neighbours = segments.get(containerCandidates[k]);

                        bool is_first = neighbours.getFirst() == originalIndex;

                        int otherNeighbour = is_first? neighbours.getSecond() : neighbours.getFirst();

                        segments.insert(edge, NeighboursBySegment(index, otherNeighbour));

                        std::unordered_map<IndexSegment,std::vector<IndexSegment>,SegmentHasher>& polyInfo =
                                changesInNeighbours[otherNeighbour];
                        polyInfo[containerCandidates[k]].push_back(edge);

                        changed = true;
                        break;
                    }
                }

                if(!changed){
                    segments.insert(edge, index);
                }
            }else{
                segments.insert(edge,index);
            }
        }
    }

    for(auto value: changesInNeighbours){
        if(value.first<0)
            continue;

        xPolygon poly = meshElements[value.first];

        for(auto s: value.second){
            poly.replaceSegment(s.first, s.second, meshPoints.getList());
        }
    }
}

