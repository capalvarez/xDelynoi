#include <xDelynoi/operations/MeshOperator.h>

MeshOperator::MeshOperator() {}

void MeshOperator::setMesh(xMeshElements*& mesh) {
    this->mesh = mesh;
}
