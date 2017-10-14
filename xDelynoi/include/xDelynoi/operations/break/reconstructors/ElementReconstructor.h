#ifndef XDELYNOI_ELEMENTRECONSTRUCTOR_H
#define XDELYNOI_ELEMENTRECONSTRUCTOR_H

#include <xDelynoi/models/constructor/ElementConstructor.h>
#include <xDelynoi/models/xPolygon.h>

class ElementReconstructor {
protected:
    ElementConstructor* constructor;
public:
    ElementReconstructor(ElementConstructor* constructor);
    virtual std::vector<xPolygon*> reconstructElement(std::vector<int> points, std::vector<Point> meshPoints) = 0;
};

#endif