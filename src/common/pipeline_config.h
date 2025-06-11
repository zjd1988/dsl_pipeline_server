/********************************************
// Filename: pipeline_config.h
// Created by zhaojiadi on 2023/4/29
// Description:

********************************************/
#pragma once
#include <map>
#include <vector>
#include <string>

namespace DslPipelineServer
{

    typedef enum ComponentType
    {
        INVALID_COMPONENT_TYPE                          = -1,
        SOURCE_COMPONENT_TYPE                           = 0,
        PREPROCESS_COMPONENT_TYPE                       = 1,
        INFER_ENGINE_COMPONENT_TYPE                     = 2,
        INFER_SERVICE_COMPONENT_TYPE                    = 3,
        MULTI_OBJ_TRACKER_COMPONENT_TYPE                = 4,
        MULTI_SOURCE_TILER_COMPONENT_TYPE               = 5,
        OSD_COMPONENT_TYPE                              = 6,
        SINK_COMPONENT_TYPE                             = 7,
        TEE_COMPONENT_TYPE                              = 8,
        BRANCH_COMPONENT_TYPE                           = 9,
        REMUXER_COMPONENT_TYPE                          = 10,
        PPH_COMPONENT_TYPE                              = 11
    } ComponentType;

    typedef struct SourceCompConfig
    {

    } SourceCompConfig;

    typedef struct PrePorcessCompConfig
    {

    } PrePorcessCompConfig;

    typedef struct InferEngineCompConfig
    {

    } InferEngineCompConfig;

    typedef struct InferServiceCompConfig
    {

    } InferServiceCompConfig;

    typedef struct MultiObjTrackerCompConfig
    {

    } MultiObjTrackerCompConfig;

    typedef struct MultiSourceTilerCompConfig
    {

    } MultiSourceTilerCompConfig;

    typedef struct OsdCompConfig
    {

    } OsdCompConfig;

    typedef struct SinkCompConfig
    {

    } SinkCompConfig;

    typedef struct TeeCompConfig
    {

    } TeeCompConfig;

    typedef struct BranchCompConfig
    {

    } BranchCompConfig;

    typedef struct RemuxerCompConfig
    {

    } RemuxerCompConfig;

    typedef struct PPHCompConfig
    {

    } PPHCompConfig;

    typedef struct ComponentConfig
    {
        ComponentType                                   comp_type;
        std::string                                     comp_name;
        union
        {
            SourceCompConfig                            source_config;
            PrePorcessCompConfig                        preprocess_config;
            InferEngineCompConfig                       infer_engine_config;
            InferServiceCompConfig                      infer_service_config;
            MultiObjTrackerCompConfig                   multi_obj_tracker_config;
            MultiSourceTilerCompConfig                  multi_source_tiler_config;
            OsdCompConfig                               osd_config;
            SinkCompConfig                              sink_config;
            TeeCompConfig                               tee_config;
            BranchCompConfig                            branch_config;
            RemuxerCompConfig                           remuxer_config;
            PPHCompConfig                               pph_config;
        };
    } ComponentConfig;

    typedef struct PipelineConfig
    {
        std::vector<std::string>                         components;
        std::map<std::string, ComponentConfig>           component_config;
    } PipelineConfig;

} // namespace DslPipelineServer