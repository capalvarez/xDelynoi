#ifndef XDELYNOI_CONTAINERINFO_H
#define XDELYNOI_CONTAINERINFO_H

#include <xDelynoi/models/xPolygon.h>

struct ContainerInfo {
    Point point;
    std::vector<int> containers;
    bool insidePolygon = false;
    bool inVertex = false;
    bool inEdge = false;
    bool isInBoundary = false;

    ContainerInfo() {}

    ContainerInfo(Point p, int container) {
        point = p;
        containers.push_back(container);
        insidePolygon = true;
    }

    ContainerInfo(Point p, int container1, int container2) {
        point = p;
        if (container1 != -1) {
            containers.push_back(container1);
        }

        if (container2 != -1) {
            containers.push_back(container2);
        }

        inEdge = true;
    }

    ContainerInfo(Point p, std::vector<int> c) {
        point = p;
        containers.assign(c.begin(), c.end());
        inVertex = true;
    }

    void setAsBoundary(bool set){
        isInBoundary = set;
    }

    bool isInsideDomain(){
        return !containers.empty();
    }

};

#endif