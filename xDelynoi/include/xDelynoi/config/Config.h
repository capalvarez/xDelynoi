#ifndef XDELYNOI_CONFIG_H
#define XDELYNOI_CONFIG_H

#include <xDelynoi/operations/MeshRefiner.h>
#include <xDelynoi/operations/MeshMerger.h>
#include <xDelynoi/models/xMesh.h>
#include "Configurations.h"

class Config{
public:
    MeshRefiner* refiner;
    MeshMerger* merger;
    ElementReconstructor* reconstructor;
    ClosingRule* closingRule;

    Config(MeshRefiner* refiner, MeshMerger* merger, ElementReconstructor* reconstructor, ClosingRule* closingRule){
        this->refiner = refiner;
        this->merger = merger;
        this->reconstructor = reconstructor;
        this->closingRule = closingRule;
    }

    void setMesh(xMeshElements*& mesh){
        this->refiner->setMesh(mesh);
        this->merger->setMesh(mesh);
    }

    explicit Config(Configurations::config config){
        config_info info = Configurations::configurations[config];

        this->refiner = info.refiner;
        this->merger = info.merger;
        this->reconstructor = info.reconstructor;
        this->closingRule = info.closingRule;
    }
};

#endif