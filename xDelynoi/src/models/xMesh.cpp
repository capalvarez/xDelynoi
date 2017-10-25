#include <xDelynoi/models/xMesh.h>
#include <delynoi/models/generator/PointGenerator.h>
#include <delynoi/models/Region.h>
#include <xDelynoi/utilities/xdelynoi_utilities.h>
#include <xDelynoi/models/structures/greater.h>
#include <xDelynoi/operations/break/functions/break_functions.h>


xMesh::xMesh(Mesh<Triangle> mesh, Config config) {
    for(const Triangle e: mesh.getPolygons()){
        xPolygon newElement(e);

        this->polygons.push_back(newElement);
    }

    this->points = mesh.getPoints();

    this->xpointMap = new xPointMap(*mesh.getPointMap());
    this->pointMap =  this->xpointMap;
    this->xEdges = new xSegmentMap(*mesh.getSegments());
    this->edges = this->xEdges;

    this->elements = new xMeshElements(this->getPointsPointer(), this->getPolygonsPointer(), this->xEdges, this->xpointMap);

    config.setMesh(this->elements);

    this->merger = config.merger;
    this->refiner = config.refiner;
    this->reconstructor = config.reconstructor;
    this->closingRule = config.closingRule;
}

xMesh::xMesh(Mesh<Polygon> mesh, Config config) {
    for(const Polygon e: mesh.getPolygons()){
        xPolygon newElement(e);

        this->polygons.push_back(newElement);
    }

    this->points = mesh.getPoints();

    this->xpointMap = new xPointMap(*mesh.getPointMap());
    this->pointMap =  this->xpointMap;
    this->xEdges = new xSegmentMap(*mesh.getSegments());
    this->edges = this->xEdges;

    this->elements = new xMeshElements(this->getPointsPointer(), this->getPolygonsPointer(), this->xEdges, this->xpointMap);
    config.setMesh(this->elements);

    this->merger = config.merger;
    this->refiner = config.refiner;
    this->reconstructor = config.reconstructor;
    this->closingRule = config.closingRule;
}

xMesh::xMesh(const xMesh &m) {
    this->points.push_list(m.getPoints());
    std::vector<xPolygon> polygons = m.getPolygons();

    this->polygons.assign(polygons.begin(), polygons.end());
    this->xEdges = new xSegmentMap(*m.getSegments());
    this->edges = this->xEdges;
    this->xpointMap = new xPointMap(*m.getPointMap());
    this->pointMap =  this->xpointMap;

    this->elements = new xMeshElements(this->getPointsPointer(), this->getPolygonsPointer(), this->xEdges, this->xpointMap);

    this->merger = (MeshMerger*) m.merger->clone();
    this->merger->setMesh(this->elements);

    this->refiner = (MeshRefiner*) m.refiner->clone();
    this->refiner->setMesh(this->elements);

    this->reconstructor = m.reconstructor;
    this->closingRule = m.closingRule;
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
            xEdges->changeNeighbour(s, first, last);
        }
    }

    for(IndexSegment s: lastSegments) {
        auto got = toIgnore.find(s);

        if (got == toIgnore.end()) {
            xEdges->changeNeighbour(s, last, first);
        }
    }

    for(Point p: p1.getPoints(this->points.getList())){
        xpointMap->changeNeighbour(p, first, last);
    }

    for(Point p: p2.getPoints(this->points.getList())){
        xpointMap->changeNeighbour(p, last, first);
    }


    this->polygons[first] = p2;
    this->polygons[last] = p1;
}

int xMesh::replaceElementsForMerged(std::vector<int> merged, std::vector<int> polys, std::vector<int> deletedPoints) {
    xPolygon newPolygon (merged, this->points);

    std::sort(polys.begin(), polys.end(), greater());
    this->polygons[polys.back()] = newPolygon;

    for (int j = 0; j < merged.size(); ++j) {
        xpointMap->insert(this->getPoint(merged[j]), polys.back());
    }

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
            xEdges->replaceOrDelete(s, this->polygons.size() - 1, i2, polys.back(), map, toIgnore, swappedIndexes);
        }

        this->polygons.pop_back();
    }

    for(int point: deletedPoints){
        Point p = this->getPoint(point);
        swapPoints(point, points.size()-1);
        std::vector<Point>& points = this->points.getList();
        points.pop_back();

        xpointMap->deleteElement(p);
    }

    return polys.back();
}

UniqueList<Point> *xMesh::getPointsPointer() {
    return &this->points;
}

std::vector<xPolygon> *xMesh::getPolygonsPointer() {
    return &this->polygons;
}

void xMesh::breakPolygons(NeighbourInfo n1, NeighbourInfo &n2, int init) {
    UniqueList<Point>& points = this->points;
    std::vector<xPolygon>& polygons = this->polygons;

    xPolygon poly1 = polygons[n1.neighbour];
    std::vector<int> poly1_points = poly1.getPoints();

    //Include new points on the mesh
    int p1 = points.push_back(n1.intersection);
    int p2 = points.push_back(n2.intersection);

    //Split the old polygon and generate new ones
    std::vector<int> new1 = {p1, p2};
    std::vector<int> new2 = {p2, p1};

    break_functions::partitionPolygonFromSegment(this->getElements(), reconstructor, n1, n2, poly1, new1, new2, p1, p2, init);
}

void xMesh::breakMesh(PointSegment segment) {
    int init, initialPolygon, lastPolygon;
    NeighbourInfo initialInfo;
    std::vector<int> previous;

    UniqueList<Point>& points = this->points;
    std::vector<xPolygon> polygons = this->polygons;
    xSegmentMap* edges = this->xEdges;

    ContainerInfo initialContainer = findContainer(segment.getFirst());

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
        int nextPolygon = getNeighbourFromCommonVertexSet(segment, initialContainer.containers, vertexIndex);

        for (int i: initialContainer.containers){
            if(i!=nextPolygon){
                initialPolygon = i;
                break;
            }
        }
    }

    NeighbourInfo n1 = getNeighbour(initialPolygon, segment, previous);
    initialInfo = n1;
    int last = initialPolygon;

    //If the initial point lies in the boundary, still include an extra point in the mesh
    if(initialContainer.isInBoundary){
        IndexSegment container_edge = polygons[initialContainer.containers[0]].containerEdge(points.getList(),
                                                                                             segment.getFirst());

        if(!isEndPoint(container_edge, segment.getFirst())){
            NeighbourInfo n0 = NeighbourInfo(initialContainer.containers[0], container_edge, segment.getFirst() ,false);

            breakPolygons(n0, n1, -1);
            last = polygons.size() - 1;
        }
    }

    bool oneLastIteration = false;
    init = initialPolygon;

    int i = 0;
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

        NeighbourInfo n2 = getNeighbour(n1.neighbour, segment, previous);

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

        std::string step = "step" + utilities::toString(i) + ".txt";
        this->printInFile(step);
        i++;
    }

    xMeshElements* elements = this->getElements();

    closingRule->closePolygon(elements, segment.getFirst(), initialPolygon, initialInfo);
    this->printInFile("afterFirst.txt");
    closingRule->closePolygon(elements, segment.getSecond(), lastPolygon, n1);
}

void xMesh::breakMesh(std::vector<PointSegment> segments) {

}


void xMesh::erase(Point p) {
    int i = utilities::indexOf(this->points.getList(), p);

    if(i<0){
        throw std::invalid_argument("Can not erase a non existent point");
    }

    std::vector<int> containers = xpointMap->get(p).getNeighbours();
    std::vector<int> merged = merger->mergeElements(containers);

    replaceElementsForMerged(merged, containers, {i});
}

void xMesh::erase(xPolygon elem) {
    int i = utilities::indexOf(this->polygons, elem);

    if(i<0){
        throw std::invalid_argument("Can not erase a non existent mesh element");
    }

    std::vector<int> neighbours = getNeighboursByPoint(i);
    neighbours.push_back(i);

    this->mergeElements(neighbours);
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
    std::vector<int> containersP1 = xpointMap->get(this->getPoint(point1)).getNeighbours();
    std::vector<int> containersP2 = xpointMap->get(this->getPoint(point2)).getNeighbours();

    for(int i: containersP1){
        this->getPolygon(i).replaceVertex(point1, point2, this->xEdges);
    }

    for(int i: containersP2){
        this->getPolygon(i).replaceVertex(point2, point1, this->xEdges);
    }

    Point p1 = this->getPoint(point1);
    Point p2 = this->getPoint(point2);

    this->points[point1] = p2;
    this->points[point2] = p1;
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
    std::vector<int> elements = {elem1, elem2};
    mergeElements(elements);
}

void xMesh::mergeElements(std::vector<int> elements) {
    std::vector<int> merged = merger->mergeElements(elements);
    std::vector<std::vector<int>> lists;

    for(int n: elements){
        lists.push_back(this->getPolygon(n).getPoints());
    }

    std::vector<int> deletedPoints = vector_ops::difference(vector_ops::mergeVectors(lists), merged);

    replaceElementsForMerged(merged, elements, deletedPoints);
}

void xMesh::fix(MeshFixer *fixer) {
    fixer->fixMesh();
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

        NeighboursBySegment edge = this->edges->get(polySeg[j]);

        int next_poly = edge.getFirst()!=poly_index? edge.getFirst() : edge.getSecond();
        auto find = std::find(previous.begin(), previous.end(), next_poly);
        if(next_poly==-1 || find!=previous.end()){
            continue;
        }

        // Special case: Intersection through vertex
        int vertexIndex;
        if(poly.isVertex(p, this->points.getList(), vertexIndex)){
            NeighboursByPoint neighbourInfo = this->pointMap->get(this->points[vertexIndex]);
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
    ContainerInfo container = this->findContainer(p);

    if(!container.isInsideDomain() || container.inVertex){
        return;
    }

    if (container.isInBoundary) {
        xPolygon elem = this->getPolygon(container.containers[0]);
        IndexSegment containerSegment = elem.containerEdge(this->getPoints().getList(), p);

        int index = this->points.push_back(p);
        elem.insertOnSegment(containerSegment, index);
    }

    if(container.inEdge) {
        std::vector<int> merged = this->merger->mergeElements(container.containers);
        std::vector<std::vector<int>> lists;

        for (int n: container.containers) {
            lists.push_back(this->getPolygon(n).getPoints());
        }

        std::vector<int> deleted = vector_ops::difference(vector_ops::mergeVectors(lists), merged);
        UniqueList<Point> toRefine;
        for (int i : deleted) {
            Point toBeDeleted = this->getPoint(i);
            toRefine.push_back(toBeDeleted);
        }

        int mergedPolygon = replaceElementsForMerged(merged, container.containers, deleted);
        toRefine.push_back(p);

        this->refiner->refine(this->getPolygon(mergedPolygon), toRefine.getList());
        return;
    }

    xPolygon elem = this->getPolygon(container.containers[0]);
    this->refiner->refine(elem, {p});

    this->printInFile("afterRefining.txt");
}

void xMesh::refine(std::vector<Point> p) {
    for (Point point: p){
        this->refine(point);
    }
}

void xMesh::refine(xPolygon poly, PointGenerator generator, int nX, int nY) {
    Region region(poly, this->points.getList());
    BoundingBox box = region.getBox();
    std::vector<Point> generatorPoints;

    generator.generate(generatorPoints, box, nX, nY);

    this->refiner->refine(poly, generatorPoints);
}

void xMesh::refine(xPolygon poly, PointCreator *generator) {
    std::vector<Point> generatorPoints = generator->createPoints(poly, this->points);
    //Check if points are inside the polygon, or they can not be used for refinement
    this->refiner->refine(poly, generatorPoints);
}

ContainerInfo xMesh::processContainerInfo(int poly, Point point) {
    if(poly<0){
        return ContainerInfo();
    }

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
            NeighboursByPoint n = pointMap->get(point);

            return ContainerInfo(point, n.getNeighbours());
        }else{
            NeighboursBySegment n = edges->get(container_edge);

            return ContainerInfo(point, n.getFirst(), n.getSecond());
        }
    }

    ContainerInfo info(point, poly);
    info.setAsBoundary(inBoundary);

    return info;
}


std::vector<int> xMesh::getNeighboursByPoint(int poly_index) {
    std::vector<Point> points = this->getPolygon(poly_index).getPoints(this->points.getList());

    return xpointMap->getAllNeighbours(points, poly_index);
}


std::vector<int> xMesh::getNeighboursBySegment(int poly_index) {
    std::vector<IndexSegment> segments;
    this->getPolygon(poly_index).getSegments(segments);

    return xEdges->getAllNeighbours(segments, poly_index);
}

bool xMesh::isInBorder(IndexSegment container) {
    return edges->get(container).getFirst()==-1 || edges->get(container).getSecond()==-1;
}

bool xMesh::isEndPoint(IndexSegment segment, Point p) {
    return p == points[segment.getFirst()] || p == points[segment.getSecond()];
}

xSegmentMap *xMesh::getSegments() {
    return this->xEdges;
}

xSegmentMap *xMesh::getSegments() const {
    return this->xEdges;
}

xPointMap *xMesh::getPointMap() {
    return this->xpointMap;
}

xPointMap *xMesh::getPointMap() const {
    return this->xpointMap;
}

xMeshElements* xMesh::getElements() {
    return this->elements;
}
