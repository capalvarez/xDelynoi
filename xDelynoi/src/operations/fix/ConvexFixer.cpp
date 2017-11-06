#include <xDelynoi/operations/fix/ConvexFixer.h>
#include <xDelynoi/operations/fix/PolyPartitionWrapper.h>

ConvexFixer::ConvexFixer() {}

ConvexFixer::~ConvexFixer() {
    delete partitioner;
}

void ConvexFixer::fixMesh() {
    std::vector<xPolygon>* elements = mesh->polygons;
    UniqueList<Point>* points = mesh->points;

    for(xPolygon e : *elements){
        if(e.isConvex(points->getList())){
            continue;
        }

        fixNonConvex(e);
    }
}

void ConvexFixer::fixElement(xPolygon elem) {
    UniqueList<Point>* points = mesh->points;

    if(elem.isConvex(points->getList())){
        fixNonConvex(elem);
    }
}

void ConvexFixer::fixNonConvex(xPolygon elem) {
    int elemIndex = utilities::indexOf(*this->mesh->polygons, elem);
    UniqueList<Point>* points = mesh->points;

    SimpleMesh simpleMesh = partitioner->partition(elem);

    std::unordered_map<int,int> pointMap = AddElementsAdapter::includeNewPoints(*points, simpleMesh.getPoints());
    AddElementsAdapter::includeNewElements(this->mesh, simpleMesh, pointMap, elemIndex);
}

MeshOperator *ConvexFixer::clone() {
    return new ConvexFixer;
}

void ConvexFixer::setMesh(xMeshElements *&mesh) {
    MeshOperator::setMesh(mesh);
    this->partitioner = new PolyPartitionWrapper(mesh);
}
