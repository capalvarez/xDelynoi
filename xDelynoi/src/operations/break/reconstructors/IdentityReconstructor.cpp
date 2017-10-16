#include <xDelynoi/operations/break/reconstructors/IdentityReconstructor.h>


std::vector<xPolygon>
IdentityReconstructor::reconstructElement(std::vector<int> points, UniqueList<Point> meshPoints) {
    std::vector<xPolygon> elements = {xPolygon(points, meshPoints)};
    return elements;
}
