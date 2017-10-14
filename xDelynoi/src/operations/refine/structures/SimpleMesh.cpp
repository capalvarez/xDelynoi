#include <xDelynoi/operations/refine/structures/SimpleMesh.h>

template <class T>
SimpleMesh<T>::SimpleMesh() {}

template <class T>
SimpleMesh<T>::SimpleMesh(std::vector<T> elems, UniqueList<Point> points) {
    this->points = points;
    this->elements = elems;
}

template <class T>
std::vector<T> SimpleMesh::getElements() {
    return this->elements;
}

template <class T>
std::vector<Point> SimpleMesh::getPoints() {
    return this->points.getList();
}
