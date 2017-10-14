#include <xDelynoi/operations/break/reconstructors/IdentityReconstructor.h>

IdentityReconstructor::IdentityReconstructor(ElementConstructor *constructor) : ElementReconstructor(constructor) {}

std::vector<xPolygon *>
IdentityReconstructor::reconstructElement(std::vector<int> points, UniqueList<Point> meshPoints) {
    std::vector<xPolygon*> elements = {constructor->createNewElement(points, meshPoints)};
}
