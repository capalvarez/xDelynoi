#include <xDelynoi/operations/fix/ConvexFixer.h>
#include <xDelynoi/operations/fix/PolyPartitionWrapper.h>

ConvexFixer::ConvexFixer(xMesh *mesh, ElementConstructor *constructor) {
    this->partitioner = new PolyPartitionWrapper(mesh, constructor);
    this->mesh = mesh;
    this->constructor = constructor;
}

ConvexFixer::~ConvexFixer() {
    delete partitioner;
}

void ConvexFixer::fixMesh() {
    std::vector<xPolygon*> elements = mesh->getPolygons();
    UniqueList<Point>& points = mesh->getPoints();

    for(xPolygon* e : elements){
        if(e->isConvex(points.getList())){
            continue;
        }

        fixNonConvex(e);
    }
}

void ConvexFixer::fixElement(xPolygon *elem) {
    UniqueList<Point>& points = mesh->getPoints();

    if(elem->isConvex(points.getList()){
        fixNonConvex(elem);
    }
}

void ConvexFixer::fixNonConvex(xPolygon *elem) {
    int elemIndex = utilities::indexOf(this->mesh->getPolygons(), elem);
    UniqueList<Point> &points = mesh->getPoints();

    SimpleMesh simpleMesh = partitioner->partition(elem);

    std::unordered_map<int,int> pointMap = AddElementsAdapter::includeNewPoints(points, simpleMesh.getPoints());
    AddElementsAdapter::includeNewElements(this->mesh, simpleMesh, pointMap, elemIndex, this->constructor);
}
