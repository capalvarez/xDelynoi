#ifndef XDELYNOI_ELEMENTCONSTRUCTOR_H
#define XDELYNOI_ELEMENTCONSTRUCTOR_H

#include <vector>
#include <delynoi/models/basic/Point.h>
#include <utilities/UniqueList.h>

class ElementConstructor{
public:
    virtual xPolygon* createNewElement(std::vector<int> points, UniqueList<Point> meshPoints)=0;
};

#endif