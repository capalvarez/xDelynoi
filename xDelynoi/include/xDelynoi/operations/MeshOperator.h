#ifndef XDELYNOI_MESHOPERATOR_H
#define XDELYNOI_MESHOPERATOR_H

#include <xDelynoi/models/structures/xMeshElements.h>

class MeshOperator{
protected:
    xMeshElements mesh;
public:
    MeshOperator();
    void setMesh(xMeshElements& mesh);
};

#endif