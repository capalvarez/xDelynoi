#include <xDelynoi/operations/break/reconstructors/IdentityReconstructor.h>


std::vector<xPolygon>
IdentityReconstructor::reconstructElement(std::vector<int> points, std::vector<Point> meshPoints) {
    xPolygon newPolygon(points, meshPoints);
    newPolygon.fixCCW(meshPoints);

    std::vector<xPolygon> elements = {newPolygon};
    return elements;
}
