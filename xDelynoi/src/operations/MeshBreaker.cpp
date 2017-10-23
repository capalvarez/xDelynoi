#include <xDelynoi/operations/MeshBreaker.h>
#include <xDelynoi/operations/break/functions/break_functions.h>

MeshBreaker::MeshBreaker(ClosingRule *close, ElementReconstructor *reconstructor) {
    this->closingRule = close;
    this->constructor = reconstructor;
}

void MeshBreaker::breakMesh(xMesh* mesh, PointSegment segment) {
    this->breakMesh(segment, this->closingRule);
}

void MeshBreaker::breakMesh(xMesh* mesh, std::vector<PointSegment> segments) {

}

void MeshBreaker::breakMesh(xMesh* mesh, PointSegment segment, ClosingRule *rule) {
    int init, initialPolygon, lastPolygon;
    NeighbourInfo initialInfo;
    std::vector<int> previous;

    UniqueList<Point>& points = this->mesh.points;
    std::vector<xPolygon> polygons = this->mesh.polygons;
    xSegmentMap* edges = this->mesh.segments;

    ContainerInfo initialContainer = mesh->findContainer(segment.getFirst());

    if(initialContainer.insidePolygon){
        initialPolygon = initialContainer.containers[0];
    }

    if(initialContainer.inEdge){
        xPolygon p1 = polygons[initialContainer.containers[0]];
        initialPolygon = p1.numberOfInteresectedSegments(segment, points.getList())>1? initialContainer.containers[1] :
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
    initialInfo = n1;
    int last = initialPolygon;

    //If the initial point lies in the boundary, still include an extra point in the mesh
    if(initialContainer.isInBoundary){
        IndexSegment container_edge = polygons[initialContainer.containers[0]].containerEdge(points.getList(),
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
        xPolygon poly1 = polygons[n1.neighbour];

        if(poly1.containsPoint(points.getList(), segment.getSecond())){
            if(poly1.inEdges(points.getList(), segment.getSecond())){
                if(!oneLastIteration){
                    oneLastIteration = true;
                }
            }else{
                lastPolygon = n1.neighbour;
                break;
            }
        }

        std::vector<int> poly1_points = poly1.getPoints();

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

            last = edges->getOther(n1.edge, n1.neighbour);
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

    closingRule->closePolygon(this->mesh, segment.getFirst(), initialPolygon, initialInfo);
    closingRule->closePolygon(this->mesh, segment.getSecond(), lastPolygon, n1);
}

void MeshBreaker::breakPolygons(NeighbourInfo n1, NeighbourInfo &n2, int init) {
    UniqueList<Point>& points = mesh.points;
    std::vector<xPolygon>& polygons = mesh.polygons;

    xPolygon poly1 = polygons[n1.neighbour];
    std::vector<int> poly1_points = poly1.getPoints();

    //Include new points on the mesh
    int p1 = points.push_back(n1.intersection);
    int p2 = points.push_back(n2.intersection);

    //Split the old polygon and generate new ones
    std::vector<int> new1 = {p1, p2};
    std::vector<int> new2 = {p2, p1};

    break_functions::partitionPolygonFromSegment(mesh, constructor, n1, n2, poly1, new1, new2, p1, p2, init);
}

