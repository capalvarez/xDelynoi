#include <xDelynoi/operations/refine/structures/SimpleMesh.h>
#include <delynoi/models/polygon/Triangle.h>

SimpleMesh::SimpleMesh() {}

SimpleMesh::SimpleMesh(std::vector<Polygon> elems, UniqueList<Point> points) {
    this->points = points;
    this->elements = elems;
}

SimpleMesh::SimpleMesh(std::vector<Triangle> elems, UniqueList<Point> points) {
    this->points = points;
    this->elements.assign(elems.begin(), elems.end());
}

std::vector<Polygon> SimpleMesh::getElements() {
    return this->elements;
}

std::vector<Point> SimpleMesh::getPoints() {
    return this->points.getList();
}
