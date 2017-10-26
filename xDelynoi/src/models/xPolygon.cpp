#include <xDelynoi/models/xPolygon.h>
#include <xDelynoi/models/neighbourhood/xSegmentMap.h>

xPolygon::xPolygon(Polygon polygon) {
    this->points.assign(polygon.getPoints().begin(), polygon.getPoints().end());
    this->hash = polygon.hash;
    this->area = polygon.getArea();
    this->diameter = polygon.getDiameter();
    this->centroid = polygon.getCentroid();
}

xPolygon::xPolygon(std::vector<int> points, UniqueList<Point> meshPoints) : Polygon(points, meshPoints.getList()){}

xPolygon::xPolygon(std::vector<int> points, std::vector<Point> meshPoints) : Polygon(points, meshPoints) {}

bool xPolygon::isVertex(Point p, std::vector<Point> points, int &vertexIndex) {
    for (int i: this->points){
        if(points[i]==p){
            vertexIndex = i;
            return true;
        }
    }

    return false;
}

bool xPolygon::isVertex(Point p, std::vector<Point> points) {
    int i;
    return isVertex(p, points, i);
}

bool xPolygon::isVertex(int index) {
    return Polygon::isVertex(index);
}

std::vector<IndexSegment> xPolygon::getAdjacentEdges(int i) {
    std::vector<IndexSegment> segs;
    int index = utilities::indexOf(this->points, i);
    int n = this->numberOfSides();

    if (index != -1){
        segs.push_back(IndexSegment(this->points[(n+index-1)%n], this->points[index]));
        segs.push_back(IndexSegment(this->points[index], this->points[(n+index+1)%n]));
    }

    return segs;
}

Pair<int> xPolygon::commonEdgesBorderPoints(xPolygon other, std::vector<Point> points, bool& pacman_case) {
    std::map<int,int> thisPoints;

    for (int i = 0; i < this->points.size(); ++i) {
        thisPoints[this->points[i]] = 1;
    }

    int j,k, n = other.numberOfSides();
    std::vector<int> poly_points = other.getPoints();
    int nP = other.numberOfSides();

    for (j = 0; j < nP; ++j) {
        auto search = thisPoints.find(poly_points[j]);

        if(search != thisPoints.end() && (thisPoints.find(poly_points[(j-1+nP)%nP])!=thisPoints.end() ||
                                          thisPoints.find(poly_points[(j+1)%nP])!=thisPoints.end())) {
            break;
        }
    }

    k = (j + 1)%n;
    int i = 0;
    bool last = true;
    std::vector<int> border;

    while (i<n){
        bool now = thisPoints[poly_points[k]]==0;
        bool next = thisPoints[poly_points[(k+1)%n]]==1;

        if(now && last){
            if(thisPoints[poly_points[(n+k-2)%n]]==1){
                border.push_back(poly_points[(k-1+n)%n]);
            }
        }

        if(!now && !last && next){
            border.push_back(poly_points[k]);
        }

        last = thisPoints[poly_points[k]]==1;
        k = (k+1)%n;
        i++;
    }

    if(border.size()==0){
        pacman_case = true;
        if(this->containsPoint(points, other.getCentroid())){
            //polygon is inside, do something
            return Pair<int>(-1,-1);
        }else{
            std::vector<IndexSegment> s;
            other.getSegments(s);

            return this->segmentNotContained(s);
        }
    }


    return Pair<int>(border[0], border.back());
}

Pair<int> xPolygon::segmentNotContained(std::vector<IndexSegment> s) {
    for (IndexSegment segment: s) {
        if(!containsEdge(segment)){
            return Pair<int>(segment.getFirst(), segment.getSecond());
        }
    }
    return Pair<int>(-1,-1);
}

std::vector<IndexSegment> xPolygon::surroundingVertices(int vertexIndex) {
    int i = utilities::indexOf(this->points, vertexIndex);
    if(i<0){
        return std::vector<IndexSegment>();
    }

    int n = numberOfSides();
    std::vector<IndexSegment> segs = {IndexSegment((n + i - 1)%n, i), IndexSegment(i, (i+1)%n)};

    return segs;
}

void xPolygon::replaceVertex(int oldVertex, int newVertex, xSegmentMap* edges) {
    bool changePrev = false, changeNext = false;
    NeighboursBySegment nPrev, nNext;

    int n = this->numberOfSides();
    int i = utilities::indexOf(this->points, oldVertex);

    IndexSegment prev(this->points[(n+i-1)%n], this->points[i]);
    IndexSegment next(this->points[i], this->points[(n+i+1)%n]);

    if(edges->containsSegment(prev)){
        nPrev = edges->get(prev);
        edges->deleteElement(prev);
        changePrev = true;
    }

    if(edges->containsSegment(next)){
        nNext = edges->get(next);
        edges->deleteElement(next);
        changeNext = true;
    }

    if(i>=0){
        this->points[i] = newVertex;
    }

    if(changePrev){
        prev = IndexSegment(this->points[(n+i-1)%n], this->points[i]);
        edges->insert(prev, nPrev);
    }


    if(changeNext){
        next = IndexSegment(this->points[i], this->points[(n+i+1)%n]);
        edges->insert(next, nNext);
    }
}

void xPolygon::replaceSegment(IndexSegment seg, std::vector<IndexSegment> segs, std::vector<Point> points) {
    if(segs.size()==1 && seg == segs[0])
        return;

    std::vector<int> orderedSegments;
    IndexSegment segment = segs[segs.size()-1];

    if(segment.isCCW(points,this->centroid)){
        orderedSegments.push_back(segment.getFirst());
        orderedSegments.push_back(segment.getSecond());
    }else{
        orderedSegments.push_back(segment.getSecond());
        orderedSegments.push_back(segment.getFirst());
    }

    segs.pop_back();
    int i = segs.size()-1;

    while(segs.size()!=0) {
        if(i<0){
            i = segs.size()-1;
        }

        segment = segs[i];
        segment.orderCCW(points,this->centroid);

        if(segment.isVertex(orderedSegments.front())){
            orderedSegments.insert(orderedSegments.begin(), segment.getFirst());
            segs.erase(segs.begin()+i);
            i--;
            continue;
        }

        if(segment.isVertex(orderedSegments.back())){
            orderedSegments.push_back(segment.getSecond());
            segs.erase(segs.begin()+i);
            i--;
            continue;
        }

        i--;
    }

    seg.orderCCW(points, this->getCentroid());
    int indexOfStart = utilities::indexOf(this->points, seg.getFirst());

    if(indexOfStart==this->numberOfSides()-1){
        this->points.insert(this->points.end(), orderedSegments.begin()+1, orderedSegments.end()-1);
    } else{
        this->points.insert(this->points.begin()+indexOfStart+1, orderedSegments.begin()+1, orderedSegments.end()-1);
    }
}

int xPolygon::numberOfInteresectedSegments(PointSegment direction, std::vector<Point> points) {
    int count = 0;
    std::vector<IndexSegment> segments;
    this->getSegments(segments);

    for(IndexSegment s: segments){
        Point p;
        if(direction.intersectionInfinite(points[s.getFirst()], points[s.getSecond()], p)){
            count++;
        }
    }

    return count;
}

void xPolygon::insertOnSegment(IndexSegment segment, int point) {
    std::vector<int> points = {point};

    insertOnSegment(segment, points);
}

void xPolygon::insertOnSegment(IndexSegment segment, std::vector<int> point) {
    int n = this->numberOfSides();

    int i = utilities::indexOf(this->points, segment.getFirst());
    int j = utilities::indexOf(this->points, segment.getSecond());

    if(i!=-1 && j!=-1 && (std::abs(i-j)==1 || std::abs(i-j)==(n-1))){
        int start = std::min(i,j);
        int end = std::max(i,j);

        if(start==0 && end==n-1){
            this->points.insert(this->points.end(), point.begin(), point.end());
        }else{
            this->points.insert(this->points.begin()+start+1, point.begin(), point.end());
        }

    }
}

IndexSegment xPolygon::getOtherContainer(IndexSegment segment, int vertexIndex) {
    std::vector<IndexSegment> segments = this->surroundingVertices(vertexIndex);
    return segments[0]==segment? segments[1] : segments[0];
}
