#ifndef XDELYNOI_MESHFIXER_H
#define XDELYNOI_MESHFIXER_H

#include <xDelynoi/models/xMesh.h>

class MeshFixer{
public:
    virtual void fixMesh()=0;
    virtual void fixElement(xPolygon elem)=0;
};

#endif