#include <xDelynoi/operations/MeshBreaker.h>

MeshBreaker::MeshBreaker(xMesh *mesh, ClosingRule *close) {
    this->closingRule = close;
    this->mesh = mesh;
}

void MeshBreaker::breakMesh(PointSegment segment) {
    this->breakMesh(segment, this->closingRule);
}

void MeshBreaker::breakMesh(PointSegment segment, ClosingRule *rule) {
    int init, initialPolygon, lastPolygon;
    std::vector<int> previous;

    UniqueList<Point>& points = mesh->getPoints();
    std::vector<xPolygon*> polygons = mesh->getPolygons();
    xSegmentMap edges = mesh->getSegments();

    ContainerInfo initialContainer = mesh->findContainer(segment.getFirst());

    if(initialContainer.insidePolygon){
        initialPolygon = initialContainer.containers[0];
    }

    if(initialContainer.inEdge){
        xPolygon* p1 = mesh->getPolygon(initialContainer.containers[0]);
        initialPolygon = p1->numberOfInteresectedSegments(segment, points.getList())>1? initialContainer.containers[1] :
                         initialContainer.containers[0];
    }

    if(initialContainer.inVertex){
        int vertexIndex = utilities::indexOf(points.getList(), segment.getFirst());
        int nextPolygon = mesh->getNeighbourFromCommonVertexSet(segment, initialContainer.containers, vertexIndex);

        for (int i: initialContainer.containers){
            if(i!=nextPolygon){
                initialPolygon = i;
                break;
            }
        }
    }

    NeighbourInfo n1 = mesh->getNeighbour(initialPolygon, segment, previous);
    int last = initialPolygon;

    //If the initial point lies in the boundary, still include an extra point in the mesh
    if(initialContainer.isInBoundary){
        IndexSegment container_edge = mesh->getPolygon(initialContainer.containers[0])->containerEdge(points.getList(),
                                                                                                      segment.getFirst());

        if(!mesh->isEndPoint(container_edge, segment.getFirst())){
            NeighbourInfo n0 = NeighbourInfo(initialContainer.containers[0], container_edge, segment.getFirst() ,false);

            breakPolygons(n0, n1, -1);
            last = polygons.size() - 1;
        }
    }

    bool oneLastIteration = false;
    init = initialPolygon;

    while(true){
        xPolygon* poly1 = mesh->getPolygon(n1.neighbour);

        if(poly1->containsPoint(points.getList(), segment.getSecond())){
            if(poly1->inEdges(points.getList(), segment.getSecond())){
                if(!oneLastIteration){
                    oneLastIteration = true;
                }
            }else{
                lastPolygon = n1.neighbour;
                break;
            }
        }

        std::vector<int> poly1_points = poly1->getPoints();

        if(!n1.isVertex){
            previous = {init, last};
        }else{
            if(last==-1){
                previous.push_back(last);
            }else{
                previous = {init, last};
            }

        }

        NeighbourInfo n2 = mesh->getNeighbour(n1.neighbour, segment, previous);

        if(n1.isEdge){
            init = n1.neighbour;
            n1 = n2;

            last = edges.getOther(n1.edge, n1.neighbour);
            continue;
        }

        breakPolygons(n1, n2, init);

        // Iterate
        if(oneLastIteration){
            lastPolygon = n1.neighbour;
            break;
        }

        IndexSegment edge = n2.edge;

        last = polygons.size()-1;
        init = n1.neighbour;
        n1 = n2;
    }

    closingRule->closePolygon(mesh, segment.getFirst(), initialPolygon);
    closingRule->closePolygon(mesh, segment.getSecond(), lastPolygon);
}

std::vector<int> MeshBreaker::computeNewPolygons(NeighbourInfo n1, NeighbourInfo &n2, xPolygon *poly1,
                                                 std::vector<int> &new1, std::vector<int> &new2, int p1, int p2, int init) {
    UniqueList<Point> &points = mesh->getPoints();
    std::vector<xPolygon*>& polygons = mesh->getPolygons();

    std::vector<int> poly1_points = poly1->getPoints();

    n1.orderCCW(points.getList(), poly1->getCentroid());
    n2.orderCCW(points.getList(), poly1->getCentroid());

    int indexOfStart, point;

    if (delynoi_utilities::orientation(points[p1], points[p2], points[n2.edge.getFirst()]) >= 0) {
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

    std::vector<xPolygon *> newPolygons1 = constructor->reconstructElement(new1, points.getList());
    std::vector<xPolygon *> newPolygons2 = constructor->reconstructElement(new2, points.getList());

    newPolygons1.insert(newPolygons1.end(), newPolygons2.begin(), newPolygons2.end());

    std::vector<int> newIndexes;
    newIndexes.push_back(n1.neighbour);
    polygons[n1.neighbour] = newPolygons1[0];

    for (int i = 1; i < newPolygons1.size(); ++i) {
        polygons.push_back(newPolygons1[i]);
        newIndexes.push_back(polygons.size() - 1);
    }

    return newIndexes;
}

void MeshBreaker::breakPolygons(NeighbourInfo n1, NeighbourInfo &n2, int init) {
    UniqueList<Point>& points = mesh->getPoints();
    xSegmentMap& edges = mesh->getSegments();
    xPointMap& pointMap = mesh->getPointMap();

    xPolygon* poly1 = mesh->getPolygon(n1.neighbour);
    std::vector<int> poly1_points = poly1->getPoints();

    //Include new points on the mesh
    int p1 = points.push_back(n1.intersection);
    int p2 = points.push_back(n2.intersection);

    //Split the old polygon and generate new ones
    std::vector<int> new1 = {p1, p2};
    std::vector<int> new2 = {p2, p1};

    UniqueList<int> newPoints;
    std::vector<int> newElements = computeNewPolygons(n1, n2, poly1, new1, new2, p1, p2, init);

    if(init>=0){
        mesh->getPolygon(init)->insertOnSegment(n1.edge, p1);
    }

    mesh->getPolygon(n2.neighbour)->insertOnSegment(n2.edge, p2);

    // Get the edge information for the old polygon and update it
    if(!n1.isVertex){
        edges.deleteElement(n1.edge);
    }
    if(!n2.isVertex){
        edges.deleteElement(n2.edge);
    }

    edges.insert(IndexSegment(p1,p2),NeighboursBySegment(n1.neighbour,n1.neighbour));
    pointMap.insert(points[p1], {init, n1.neighbour, n1.neighbour});
    pointMap.insert(points[p2], {n2.neighbour, n1.neighbour, n1.neighbour});

    for(int newElem: newElements){
        xPolygon* elem = mesh->getPolygon(newElem);
        std::vector<IndexSegment> segments;
        elem->getSegments(segments);
        std::vector<int> elemPoints = elem->getPoints();

        for (IndexSegment s: segments) {
            edges.replaceNeighbour(s, n1.neighbour, newElem);
        }

        for (int j = 0; j < elemPoints.size(); ++j) {
            pointMap.replaceNeighbour(mesh->getPoint(elemPoints[j]), n1.neighbour, newElem);
        }
    }

    if(!n1.isVertex){
        edges.insert_if_null(IndexSegment(p1,n1.edge.getFirst()),init);
        edges.insert_if_null(IndexSegment(p1,n1.edge.getSecond()), init);
    }

    if(!n2.isVertex){
        edges.insert_if_null(IndexSegment(p2,n2.edge.getFirst()), n2.neighbour);
        edges.insert_if_null(IndexSegment(p2,n2.edge.getSecond()), n2.neighbour);
    }

    n2.extraPoint = p2;
}
