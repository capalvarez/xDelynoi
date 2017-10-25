#ifndef XDELYNOI_CONFIGURATIONS_H
#define XDELYNOI_CONFIGURATIONS_H

#include <map>
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
#include <xDelynoi/operations/break/closingrules/StraightLineClosingRule.h>

struct config_info{
    ElementReconstructor* reconstructor;
    ClosingRule* closingRule;
    MeshMerger* merger;
    MeshRefiner* refiner;

    config_info(){}

    config_info(ElementReconstructor* eR, ClosingRule* cR,  MeshMerger* m, MeshRefiner* r){
        reconstructor = eR;
        closingRule = cR;
        merger = m;
        refiner = r;
    }

};

namespace Configurations{
   enum class config {ForceTriangulation, TriangulationWithPolygons, PolygonalDefault, PolygonalTriangulateRefine, PolygonalBreakAddPoints};

    static std::map<Configurations::config,config_info> configurations = {
            {Configurations::config::ForceTriangulation, config_info(
                    new PolygonToTriangleReconstructor, new TriangulateClosingRule,
                    new NotAllowedMerger, new TriangulateRefiner)},
            {Configurations::config::TriangulationWithPolygons, config_info(
                    new IdentityReconstructor, new TriangulateClosingRule,
                    new VertexIndexMerger, new TriangulateRefiner)},
            {Configurations::config::PolygonalDefault, config_info(
                    new IdentityReconstructor, new ClosestVertexClosingRule,
                    new VertexIndexMerger, new VoronoiRefiner)},
            {Configurations::config::PolygonalTriangulateRefine, config_info(
                    new IdentityReconstructor, new ClosestVertexClosingRule,
                    new VertexIndexMerger, new TriangulateRefiner)},
            {Configurations::config::PolygonalBreakAddPoints, config_info(
                    new IdentityReconstructor, new StraightLineClosingRule,
                    new VertexIndexMerger, new VoronoiRefiner)}
    };
};

#endif