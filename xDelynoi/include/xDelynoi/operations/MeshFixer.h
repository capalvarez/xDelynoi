#ifndef XDELYNOI_MESHFIXER_H
#define XDELYNOI_MESHFIXER_H

#include <xDelynoi/models/xMesh.h>

class xMesh;

class MeshFixer{
public:
    virtual void fixMesh(xMesh* mesh)=0;
    virtual void fixElement(xPolygon* elem, xMesh* mesh)=0;
};

#endif