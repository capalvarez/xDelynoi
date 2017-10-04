#ifndef XDELYNOI_CONVEXFIXER_H
#define XDELYNOI_CONVEXFIXER_H

#include <xDelynoi/operations/MeshFixer.h>

class ConvexFixer: public MeshFixer {
public:
    void fixMesh(xMesh *mesh);
};

#endif