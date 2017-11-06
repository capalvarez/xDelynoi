#include <xDelynoi/operations/merge/NotAllowedMerger.h>

std::vector<int> NotAllowedMerger::mergeElements(xPolygon e1, xPolygon e2) {
    throw std::invalid_argument("Merging forbidden");
}

std::vector<int> NotAllowedMerger::mergeElements(xPolygon e1, xPolygon e2, IndexSegment segment) {
    throw std::invalid_argument("Merging forbidden");
}

std::vector<int> NotAllowedMerger::mergeElements(std::vector<int> elements) {
    throw std::invalid_argument("Merging forbidden");
}

MeshOperator *NotAllowedMerger::clone() {
    return new NotAllowedMerger;
}
