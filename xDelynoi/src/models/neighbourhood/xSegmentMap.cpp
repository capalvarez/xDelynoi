#include <xDelynoi/models/neighbourhood/xSegmentMap.h>
#include <utilities/UniqueList.h>

xSegmentMap::xSegmentMap() {}

xSegmentMap::xSegmentMap(SegmentMap segmentMap) {
    this->map = segmentMap.getMap();
}

void xSegmentMap::changeNeighbour(NeighboursBySegment n, int oldN, int newN) {
    if(n.getFirst()==oldN){
        n.setFirst(newN);
        return;
    }

    if(n.getSecond()==oldN){
        n.setSecond(newN);
        return;
    }
}

bool xSegmentMap::isNeighbour(NeighboursBySegment n, int poly) {
    return n.getFirst()==poly || n.getSecond()==poly;
}

int xSegmentMap::getOther(NeighboursBySegment n, int other) {
    if(n.getFirst()==other){
        return n.getSecond();
    }

    if(n.getSecond()==other){
        return n.getFirst();
    }
}

void xSegmentMap::changeNeighbour(IndexSegment s, int oldNeighbour, int newNeighbour) {
    NeighboursBySegment& n = this->map[s];

    if(n.getFirst()==oldNeighbour){
        n.setFirst(newNeighbour);
        return;
    }

    if(n.getSecond()==oldNeighbour){
        n.setSecond(newNeighbour);
        return;
    }
}

bool xSegmentMap::isNeighbour(IndexSegment s, int poly) {
    NeighboursBySegment n = this->get(s);

    return isNeighbour(n,poly);
}

bool xSegmentMap::isInBorder(IndexSegment s) {
    NeighboursBySegment n = this->get(s);

    return n.getFirst()<0 || n.getSecond()<0;
}

void xSegmentMap::replaceOrDelete(IndexSegment s, int oldNeighbour_current, int oldNeighbour_old, int newNeighbour,
                                  std::unordered_map<NeighboursBySegment, int, NeighboursHasher> map,
                                  std::unordered_map<IndexSegment, int, SegmentHasher> &erased,
                                  std::unordered_map<int, int> newEquivalence) {
    auto is_there = erased.find(s);
    if(is_there != erased.end()) {
        return;
    }

    NeighboursBySegment& n = get(s);
    changeNeighbour(s,oldNeighbour_current, oldNeighbour_old);
    int other = getOther(n, oldNeighbour_old);

    bool wasChanged = false;
    auto hasEquivalent = newEquivalence.find(other);
    if(hasEquivalent!=newEquivalence.end()){
        changeNeighbour(n, other, hasEquivalent->second);
        wasChanged = true;
    }

    auto iter = map.find(n);

    if(iter != map.end()){
        this->deleteElement(s);
        erased[s] = 0;
    } else{
        changeNeighbour(n, oldNeighbour_old, oldNeighbour_current);
        if(wasChanged){
            changeNeighbour(n, hasEquivalent->second, other);
        }

        this->replaceNeighbour(s,oldNeighbour_current,newNeighbour);
    }
}

void xSegmentMap::deleteElement(IndexSegment s) {
    this->map.erase(s);
}

void xSegmentMap::replaceNeighbour(IndexSegment s, int oldNeighbour, int newNeighbour) {
    auto got = this->map.find(s);

    if(got == this->map.end()){
        this->insert(s, newNeighbour);
    }else{
        changeNeighbour(s,oldNeighbour, newNeighbour);
    }
}

std::vector<int> xSegmentMap::getAllNeighbours(std::vector<IndexSegment> segments, int polygon) {
    UniqueList<int> neighbours;

    for(IndexSegment s: segments){
        NeighboursBySegment n = get(s);

        neighbours.push_back(getOther(n, polygon));
    }

    return neighbours.getList();
}

int xSegmentMap::getOther(IndexSegment n, int other) {
    return getOther(this->get(n), other);
}

void xSegmentMap::insert_if_null(IndexSegment s, int index) {
    std::unordered_map<IndexSegment,NeighboursBySegment,SegmentHasher>::iterator got = this->map.find(s);

    if(got != this->map.end()){
        NeighboursBySegment& n = got->second;
        if(isNeighbour(n,-1)){
            changeNeighbour(n, -1, index);
        }
    }
}
