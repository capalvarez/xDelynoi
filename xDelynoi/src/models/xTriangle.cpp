#include <xDelynoi/models/xTriangle.h>
#include <xDelynoi/models/xPolygon.h>

xTriangle::xTriangle(Triangle triangle) : Triangle(triangle), xPolygon(triangle){}
