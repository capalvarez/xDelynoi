#ifndef XDELYNOI_CONFIGURATIONS_H
#define XDELYNOI_CONFIGURATIONS_H

#include <map>
#include <xDelynoi/operations/MeshBreaker.h>
#include <xDelynoi/operations/MeshMerger.h>
#include <xDelynoi/operations/MeshRefiner.h>
#include <xDelynoi/operations/break/closingrules/TriangulateClosingRule.h>
#include <xDelynoi/operations/merge/NotAllowedMerger.h>
#include <xDelynoi/operations/refine/TriangulateRefiner.h>
#include <xDelynoi/operations/break/closingrules/ClosestVertexClosingRule.h>
#include <xDelynoi/operations/refine/VoronoiRefiner.h>
#include <xDelynoi/operations/break/reconstructors/PolygonToTriangleReconstructor.h>
#include <xDelynoi/operations/break/reconstructors/IdentityReconstructor.h>
#include <xDelynoi/operations/merge/VertexIndexMerger.h>

struct config_info{
    MeshBreaker* breaker;
    MeshMerger* merger;
    MeshRefiner* refiner;

    config_info(){}

    config_info(MeshBreaker* b, MeshMerger* m, MeshRefiner* r){
        breaker = b;
        merger = m;
        refiner = r;
    }

};

namespace Configurations{
   enum class config {ForceTriangulation, TriangulationWithPolygons, PolygonalDefault};

    static std::map<Configurations::config,config_info> configurations = {
            {Configurations::config::ForceTriangulation, config_info(
                    new MeshBreaker(new TriangulateClosingRule, new PolygonToTriangleReconstructor),
                    new NotAllowedMerger,
                    new TriangulateRefiner)},
            {Configurations::config::TriangulationWithPolygons, config_info(
                    new MeshBreaker(new TriangulateClosingRule, new IdentityReconstructor),
                    new VertexIndexMerger,
                    new TriangulateRefiner)},
            {Configurations::config::PolygonalDefault, config_info(
                    new MeshBreaker(new ClosestVertexClosingRule, new IdentityReconstructor),
                    new VertexIndexMerger,
                    new VoronoiRefiner)}
    };
};

#endif