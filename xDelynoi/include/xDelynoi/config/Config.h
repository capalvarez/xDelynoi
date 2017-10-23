#ifndef XDELYNOI_CONFIG_H
#define XDELYNOI_CONFIG_H

#include <xDelynoi/operations/MeshRefiner.h>
#include <xDelynoi/operations/MeshMerger.h>
#include <xDelynoi/operations/MeshBreaker.h>
#include <xDelynoi/models/xMesh.h>
#include "Configurations.h"

class Config{
public:
    MeshRefiner* refiner;
    MeshMerger* merger;
    MeshBreaker* breaker;

    Config(MeshRefiner* refiner, MeshMerger* merger, MeshBreaker* breaker){
        this->refiner = refiner;
        this->merger = merger;
        this->breaker = breaker;
    }

    void setMesh(xMeshElements mesh){
        this->refiner->setMesh(mesh);
        this->merger->setMesh(mesh);
        this->breaker->setMesh(mesh);
    }

    explicit Config(Configurations::config config){
        config_info info = Configurations::configurations[config];

        this->refiner = info.refiner;
        this->merger = info.merger;
        this->breaker = info.breaker;
    }
};

#endif