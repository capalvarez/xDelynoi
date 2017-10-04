#include <xDelynoi/operations/fix/ConvexFixer.h>

void ConvexFixer::fixMesh(xMesh *mesh) {
    std::vector<xPolygon*> elements = mesh->getPolygons();
    UniqueList<Point>& points = mesh->getPoints();

    for(xPolygon* e : elements){
        if(e->isConvex(points.getList())){
            continue;
        }


    }
}
