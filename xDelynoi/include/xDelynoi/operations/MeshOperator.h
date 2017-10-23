#ifndef XDELYNOI_MESHOPERATOR_H
#define XDELYNOI_MESHOPERATOR_H

#include <xDelynoi/models/xMesh.h>

class xMesh;

class MeshOperator{
protected:
    xMesh* mesh;
public:
    void setMesh(xMesh* mesh);
};

#endif