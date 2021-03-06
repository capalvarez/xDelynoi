#include <xDelynoi/models/neighbourhood/xPointMap.h>

xPointMap::xPointMap() : PointMap(){}

xPointMap::xPointMap(PointMap pointMap) : PointMap(){
    this->map = pointMap.getMap();
}

void xPointMap::changeNeighbour(Point p, int oldNeighbour, int newNeighbour) {
    std::vector<int>& neighbours = this->map[p].getNeighbours();

    int index = utilities::indexOf(neighbours, oldNeighbour);

    if(index!=-1){
        neighbours[index] = newNeighbour;
    }
}

void xPointMap::deleteElement(Point p) {
    this->map.erase(p);
}

std::vector<int> xPointMap::getAllNeighbours(std::vector<Point> points, int poly_index) {
    UniqueList<int> neighbours;

    for(Point p: points){
        NeighboursByPoint n = get(p);

        neighbours.push_list(n.getNeighbours());
    }

    neighbours.delete_element(poly_index);

    return neighbours.getList();
}

void xPointMap::replaceNeighbour(Point p, int oldNeighbour, int newNeighbour) {
    auto got = this->map.find(p);

    if(got == this->map.end()){
        this->insert(p, newNeighbour);
    }else{
        changeNeighbour(p,oldNeighbour, newNeighbour);
    }
}
