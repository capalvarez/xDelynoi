#ifndef XDELYNOI_BREAK_FUNCTIONS_H
#define XDELYNOI_BREAK_FUNCTIONS_H

#include <xDelynoi/models/xPolygon.h>
#include <xDelynoi/models/xMesh.h>
#include <xDelynoi/operations/break/reconstructors/ElementReconstructor.h>

namespace break_functions{
    extern void partitionPolygonFromSegment(xMesh* mesh, ElementReconstructor* constructor, NeighbourInfo n1, NeighbourInfo& n2, xPolygon poly1, std::vector<int>& new1,
                                     std::vector<int>& new2, int p1, int p2, int init);
    extern std::vector<int> computeNewPolygons(xMesh* mesh, ElementReconstructor* constructor, NeighbourInfo n1, NeighbourInfo &n2, xPolygon poly1, std::vector<int> &new1,
                                               std::vector<int> &new2, int p1, int p2);
}


#endif