#include <xDelynoi/models/xMesh.h>
#include <xDelynoi/operations/merge/VertexIndexMerger.h>
#include <xDelynoi/models/structures/greater.h>
#include <xDelynoi/utilities/vector_ops.h>
#include <xDelynoi/operations/refine/TriangulateRefiner.h>

xMesh::xMesh(Mesh<Triangle> mesh) {
    for(Triangle e: mesh.getPolygons()){
        xPolygon newElement(e);

        this->polygons.push_back(newElement);
    }

    this->pointMap = xPointMap(mesh.getPointMap());
    this->edges = xSegmentMap(mesh.getSegments());
    this->merger = new VertexIndexMerger(this);
    this->refiner = new TriangulateRefiner(this);
}

xMesh::xMesh(Mesh<Polygon> mesh) {
    for(Polygon e: mesh.getPolygons()){
        xPolygon newElement (e);

        this->polygons.push_back(newElement);
    }

    this->pointMap = xPointMap(mesh.getPointMap());
    this->edges = xSegmentMap(mesh.getSegments());
    this->merger = new VertexIndexMerger(this);
}

xSegmentMap &xMesh::getSegments() {
    return this->edges;
}

xSegmentMap xMesh::getSegments() const {
    return this->edges;
}

xPointMap &xMesh::getPointMap() {
    return this->pointMap;
}

xPointMap xMesh::getPointMap() const {
    return this->pointMap;
}

void xMesh::swapElements(int first, int last, std::unordered_map<IndexSegment, int, SegmentHasher> &toIgnore) {
    xPolygon p1 = getPolygon(first);
    xPolygon p2 = getPolygon(last);

    std::vector<IndexSegment> firstSegments;
    p1.getSegments(firstSegments);

    std::vector<IndexSegment> lastSegments;
    p2.getSegments(lastSegments);

    for(IndexSegment s: firstSegments){
        auto got = toIgnore.find(s);

        if(got==toIgnore.end()){
            edges.changeNeighbour(s, first, last);
        }
    }

    for(IndexSegment s: lastSegments) {
        auto got = toIgnore.find(s);

        if (got == toIgnore.end()) {
            edges.changeNeighbour(s, last, first);
        }
    }

    for(Point p: p1.getPoints(this->points.getList())){
        pointMap.changeNeighbour(p, first, last);
    }

    for(Point p: p2.getPoints(this->points.getList())){
        pointMap.changeNeighbour(p, last, first);
    }


    this->polygons[first] = p2;
    this->polygons[last] = p1;
}

void xMesh::replaceElementsForMerged(std::vector<int> merged, std::vector<int> polys, std::vector<int> deletedPoints) {
    xPolygon newPolygon (merged, this->points);

    std::sort(polys.begin(), polys.end(), greater());
    this->polygons[polys.back()] = newPolygon;

    std::unordered_map<NeighboursBySegment,int,NeighboursHasher> map;
    std::unordered_map<IndexSegment, int,SegmentHasher> toIgnore;
    std::unordered_map<int,int> swappedIndexes;
    std::vector<Pair<int>> pairs;
    xdelynoi_utilities::getAllPairs(pairs, polys);

    for (Pair<int> p : pairs){
        NeighboursBySegment n (p);
        map[n] = 0;
    }

    for (int i = 0; i < polys.size()-1; ++i) {
        int i2 = polys[i];

        swapElements(i2, this->polygons.size() - 1, toIgnore);
        swappedIndexes[i2] = this->polygons.size()-1;

        xPolygon poly2 = getPolygon(this->polygons.size() - 1);

        std::vector<IndexSegment> poly2Segments;
        poly2.getSegments(poly2Segments);

        for(IndexSegment s: poly2Segments){
            edges.replaceOrDelete(s, this->polygons.size() - 1, i2, polys.back(), map, toIgnore, swappedIndexes);
        }

        this->polygons.pop_back();
    }

    for(int point: deletedPoints){
        Point p = this->getPoint(point);
        swapPoints(point, points.size()-1);
        std::vector<Point>& points = this->points.getList();
        points.pop_back();

        this->pointMap.deleteElement(p);
    }
}

void xMesh::breakMesh(PointSegment segment) {


}

void xMesh::breakMesh(PointSegment segment, ClosingRule *closingRule) {





}

void xMesh::erase(Point p) {
    int i = utilities::indexOf(this->points.getList(), p);

    if(i<0){
        throw std::invalid_argument("Can not erase a non existent point");
    }

    std::vector<int> containers = this->pointMap.get(p).getNeighbours();
    std::vector<int> merged = merger->mergeElements(containers);

    replaceElementsForMerged(merged, containers, {i});
}

void xMesh::erase(xPolygon elem) {
    int i = utilities::indexOf(this->polygons, elem);

    if(i<0){
        throw std::invalid_argument("Can not erase a non existent mesh element");
    }

    std::vector<int> neighbours = getNeighboursByPoint(i);
    std::vector<std::vector<int>> lists;

    for(int n: neighbours){
        lists.push_back(this->getPolygon(n).getPoints());
    }

    std::vector<int> merged = merger->mergeElements(neighbours);
    std::vector<int> deletedPoints = vector_ops::difference(vector_ops::mergeVectors(lists), merged);

    replaceElementsForMerged(merged, neighbours, deletedPoints);
}

void xMesh::swapElements(int first, int last) {
    std::unordered_map<IndexSegment,int,SegmentHasher> toIgnore;
    swapElements(first, last, toIgnore);
}

void xMesh::swapElements(xPolygon elem1, xPolygon elem2) {
    int first = utilities::indexOf(this->polygons, elem1);
    int last = utilities::indexOf(this->polygons, elem2);

    swapElements(first, last);
}

void xMesh::swapPoints(int point1, int point2) {
    std::vector<int> containersP1 = this->pointMap.get(this->getPoint(point1)).getNeighbours();
    std::vector<int> containersP2 = this->pointMap.get(this->getPoint(point2)).getNeighbours();

    for(int i: containersP1){
        this->getPolygon(i).replaceVertex(point1, point2, this->edges);
    }

    for(int i: containersP2){
        this->getPolygon(i).replaceVertex(point2, point1, this->edges);
    }
}

void xMesh::swapPoints(Point p1, Point p2) {
    int point1 = utilities::indexOf(this->points.getList(), p1);
    int point2 = utilities::indexOf(this->points.getList(), p2);

    if(point1<0 || point2<0){
        throw std::invalid_argument("Can not swap non existant points");
    }

    swapPoints(point1, point2);
}

void xMesh::mergeElements(int elem1, int elem2) {
    std::vector<int> merged = merger->mergeElements({elem1, elem2});
}

void xMesh::mergeElements(std::vector<int> elements) {
    std::vector<int> merged = merger->mergeElements(elements);

}


ContainerInfo xMesh::findContainer(Point p) {
    int i = utilities::random_integer(0,this->polygons.size()-1);

    return this->findContainer(p, i);
}

ContainerInfo xMesh::findContainer(Point p, int startElement) {
    while(true){
        bool found = false;
        xPolygon poly = this->getPolygon(startElement);

        if(poly.containsPoint(this->points.getList(), p)){
            return processContainerInfo(startElement,p);
        }else {
            PointSegment lookup(poly.getCentroid(), p);
            NeighbourInfo neighbour = getNeighbour(startElement, lookup);

            if(neighbour.neighbour>-1) {
                startElement = neighbour.neighbour;
                found = true;
            }
        }

        if (!found) {
            return findContainerLinear(p);
        }
    }
}

ContainerInfo xMesh::findContainerLinear(Point p) {
    for (int i = 0; i < this->polygons.size(); ++i) {
        if(this->polygons[i].containsPoint(this->points.getList(), p)){
            return processContainerInfo(i, p);
        }
    }

    return ContainerInfo();
}

NeighbourInfo xMesh::getNeighbour(int poly_index, PointSegment direction) {
    std::vector<int> p;
    return getNeighbour(poly_index, direction, p);
}

NeighbourInfo xMesh::getNeighbour(int poly_index, PointSegment direction, std::vector<int> &previous) {
    xPolygon poly = getPolygon(poly_index);

    std::vector<IndexSegment> polySeg;
    poly.getSegments(polySeg);

    for (int j = 0; j < polySeg.size() ; ++j) {
        Point p;
        bool intersects = polySeg[j].intersection(this->points.getList(), direction, p);

        if(!intersects){
            continue;
        }

        NeighboursBySegment edge = this->edges.get(polySeg[j]);

        int next_poly = edge.getFirst()!=poly_index? edge.getFirst() : edge.getSecond();
        auto find = std::find(previous.begin(), previous.end(), next_poly);
        if(next_poly==-1 || find!=previous.end()){
            continue;
        }

        // Special case: Intersection through vertex
        int vertexIndex;
        if(poly.isVertex(p, this->points.getList(), vertexIndex)){
            NeighboursByPoint neighbourInfo = this->pointMap.get(this->points[vertexIndex]);
            std::vector<int> neighbours = neighbourInfo.getNeighbours();
            neighbours.erase(std::remove(neighbours.begin(), neighbours.end(), poly_index));

            int neighbour = getNeighbourFromCommonVertexSet(direction, neighbours, vertexIndex);

            NeighbourInfo n(neighbour, polySeg[j], p, false);
            n.isVertex = true;

            return n;
        }

        if(!polySeg[j].isContained(direction, this->points.getList())){
            if(find == previous.end()) {
                if(polySeg[j].isInCorner(p, this->points.getList(), vertexIndex)){
                    xPolygon nextPoly = getPolygon(next_poly);
                    std::vector<IndexSegment> candidateSegments = nextPoly.getAdjacentEdges(vertexIndex);

                    bool isInEdge = candidateSegments[0].isContained(direction, this->points.getList()) ||
                                    candidateSegments[1].isContained(direction, this->points.getList());

                    return NeighbourInfo(next_poly, polySeg[j], p, isInEdge);
                }

                return NeighbourInfo(next_poly, polySeg[j], p);
            }
        }
    }

    return NeighbourInfo(-1,IndexSegment(),Point(), false);
}

int xMesh::getNeighbourFromCommonVertexSet(PointSegment direction, std::vector<int> vertexSet, int vertexIndex) {
    int correctNeighbour = 0;
    for(int p: vertexSet){
        xPolygon candidate = this->getPolygon(p);

        if(!candidate.isVertex(vertexIndex)){
            continue;
        }

        if(candidate.numberOfInteresectedSegments(direction, this->points.getList())==2){
            correctNeighbour = p;
        }
    }

    return correctNeighbour;
}

void xMesh::refine(Point p) {

}

void xMesh::refine(std::vector<Point> p) {

}

xPolygon xMesh::getPolygon(int index) {
    return this->polygons[index];
}

ContainerInfo xMesh::processContainerInfo(int poly, Point point) {
    xPolygon polygon = getPolygon(poly);
    bool inBoundary = false;

    IndexSegment container_edge = polygon.containerEdge(this->points.getList(), point);

    if(container_edge.getFirst()!=-1){
        int vertexIndex = -1;

        if(getPoint(container_edge.getFirst())==point){
            vertexIndex = container_edge.getFirst();
        }else{
            if(getPoint(container_edge.getSecond())==point){
                vertexIndex = container_edge.getSecond();
            }
        }

        if(isInBorder(container_edge)){
            inBoundary = true;
        }

        if(vertexIndex!=-1){
            NeighboursByPoint n = pointMap.get(point);

            return ContainerInfo(point, n.getNeighbours());
        }else{
            NeighboursBySegment n = edges.get(container_edge);

            return ContainerInfo(point, n.getFirst(), n.getSecond());
        }
    }

    ContainerInfo info(point, poly);
    info.setAsBoundary(inBoundary);

    return info;
}


std::vector<int> xMesh::getNeighboursByPoint(int poly_index) {
    std::vector<Point> points = this->getPolygon(poly_index).getPoints(this->points.getList());

    return this->pointMap.getAllNeighbours(points, poly_index);
}


std::vector<int> xMesh::getNeighboursBySegment(int poly_index) {
    std::vector<IndexSegment> segments;
    this->getPolygon(poly_index).getSegments(segments);

    return this->edges.getAllNeighbours(segments, poly_index);
}

bool xMesh::isInBorder(IndexSegment container) {
    return edges.get(container).getFirst()==-1 || edges.get(container).getSecond()==-1;
}

bool xMesh::isEndPoint(IndexSegment segment, Point p) {
    return p == points[segment.getFirst()] || p == points[segment.getSecond()];
}

