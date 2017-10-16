#ifndef XDELYNOI_REFINEADAPTER_H
#define XDELYNOI_REFINEADAPTER_H

#include <delynoi/models/basic/Point.h>
#include <unordered_map>
#include <utilities/UniqueList.h>
#include <xDelynoi/models/xMesh.h>
#include <delynoi/models/basic/Angle.h>
#include <xDelynoi/operations/refine/structures/SimpleMesh.h>
#include <xDelynoi/models/xMesh.h>

class xMesh;

class AddElementsAdapter {
public:
    static std::unordered_map<int, int> includeNewPoints(UniqueList<Point> &meshPoints, std::vector<Point> points);
    static void includeNewElements(xMesh *mesh, SimpleMesh toInclude, std::unordered_map<int, int> pointMap, int originalIndex,
                                       ElementConstructor *constructor);
};

#endif