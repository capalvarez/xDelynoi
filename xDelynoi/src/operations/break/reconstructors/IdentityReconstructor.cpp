#include <xDelynoi/operations/break/reconstructors/IdentityReconstructor.h>


std::vector<xPolygon>
IdentityReconstructor::reconstructElement(std::vector<int> points, std::vector<Point> meshPoints) {
    std::vector<xPolygon> elements = {xPolygon(points, meshPoints)};
    return elements;
}
