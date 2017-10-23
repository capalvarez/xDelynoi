#include <xDelynoi/models/creator/CentroidPointCreator.h>

std::vector<Point> CentroidPointCreator::createPoints(xPolygon poly, UniqueList<Point> points) {
    return {poly.getCentroid()};
}
