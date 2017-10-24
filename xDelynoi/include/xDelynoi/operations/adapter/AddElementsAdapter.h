#ifndef XDELYNOI_REFINEADAPTER_H
#define XDELYNOI_REFINEADAPTER_H

#include <delynoi/models/basic/Point.h>
#include <unordered_map>
#include <utilities/UniqueList.h>
#include <delynoi/models/basic/Angle.h>
#include <xDelynoi/operations/refine/structures/SimpleMesh.h>
#include <xDelynoi/models/basic/xIndexSegment.h>
#include <xDelynoi/models/structures/xMeshElements.h>


class AddElementsAdapter {
public:
    static std::unordered_map<int, int> includeNewPoints(UniqueList<Point> &meshPoints, std::vector<Point> points);
    static void includeNewElements(xMeshElements* mesh, SimpleMesh toInclude, std::unordered_map<int, int> pointMap, int originalIndex);
};

#endif