/********************************************
// Filename: pipeline_config.h
// Created by zhaojiadi on 2023/4/29
// Description:

********************************************/
#pragma once
#include <map>
#include <vector>
#include <string>
#include "common/logger.h"
#include "component/source_config.h"
#include "component/sink_config.h"
#include "component/infer_config.h"
#include "component/tracker_config.h"
#include "component/osd_config.h"

namespace DslPipelineServer
{

    typedef enum ComponentType
    {
        INVALID_COMPONENT_TYPE                          = -1,
        SOURCE_COMPONENT_TYPE                           = 0,
        PREPROCESS_COMPONENT_TYPE                       = 1,
        INFER_COMPONENT_TYPE                            = 2,
        TRACKER_COMPONENT_TYPE                          = 3,
        TILER_COMPONENT_TYPE                            = 4,
        OSD_COMPONENT_TYPE                              = 5,
        SINK_COMPONENT_TYPE                             = 6,
        TEE_COMPONENT_TYPE                              = 7,
        BRANCH_COMPONENT_TYPE                           = 8,
        REMUXER_COMPONENT_TYPE                          = 9,
        PPH_COMPONENT_TYPE                              = 10,
        MAX_COMPONENT_TYPE,
    } ComponentType;

    typedef struct PrePorcessCompConfig
    {

    } PrePorcessCompConfig;

    typedef struct TilerCompConfig
    {

    } TilerCompConfig;

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
        std::string                                     name;
        ComponentType                                   type;
        union
        {
            SourceCompConfig                            source_config;
            PrePorcessCompConfig                        preprocess_config;
            InferCompConfig                             infer_config;
            TrackerCompConfig                           tracker_config;
            TilerCompConfig                             tiler_config;
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
        std::string                                      name;
        std::vector<std::string>                         component_names;
        std::map<std::string, ComponentConfig>           component_configs;
    } PipelineConfig;

    void logValidPipelineCompType();
    int convertStrToComponentType(const std::string type_str, ComponentType& type);
    int convertComponentTypeToStr(const ComponentType type, std::string& type_str);
    int parsePipelineConfigFromStr(const std::string& config_str, PipelineConfig& config);
    int parsePipelineConfigFromFile(const std::string& config_file, PipelineConfig& config);
    extern std::map<std::string, ComponentType> gStrToComponentType;
    extern std::map<ComponentType, std::string> gComponentTypeToStr;

} // namespace DslPipelineServer