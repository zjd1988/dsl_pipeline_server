/********************************************
// Filename: infer_config.h
// Created by zhaojiadi on 2023/4/29
// Description:

********************************************/
#pragma once
#include <map>
#include <vector>
#include <string>
#include <yaml-cpp/yaml.h>

namespace DslPipelineServer
{

    typedef enum InferCompType
    {
        INVALID_INFER_COMP_TYPE                         = -1,
        PRIMARY_GIE_INFER_COMP_TYPE                     = 0,      // Primary GIE
        SECONDARY_GIE_INFER_COMP_TYPE                   = 1,      // Secondary GIE
        PRIMARY_TIS_INFER_COMP_TYPE                     = 2,      // Primary TIS
        SECONDARY_TIS_INFER_COMP_TYPE                   = 3,      // Secondary TIS
        MAX_INFER_COMP_TYPE,
    } InferCompType;

    typedef struct PrimaryGieInferCompConfig
    {
        std::string                                     config_file;     // relative or absolute file path/name for the infer config file to load
        std::string                                     engine_file;     // relative or absolute file path/name for the model engine file to load. Set to NULL and the GIE Plugin will attempt to create a model-engine file based on the configuration file.
        uint32_t                                        interval;        // frame interval to infer on
    } PrimaryGieInferCompConfig;

    typedef struct SecondaryGieInferCompConfig
    {
        std::string                                     config_file;     // relative or absolute file path/name for the infer config file to load
        std::string                                     engine_file;     // relative or absolute file path/name for the model engine file to load. Set to NULL and the GIE Plugin will attempt to create a model-engine file based on the configuration file.
        std::string                                     infer_on_gie;    // unique name of the Primary or Secondary GIE to infer on
        uint32_t                                        interval;        // frame interval to infer on
    } SecondaryGieInferCompConfig;

    typedef struct PrimaryTisInferCompConfig
    {
        std::string                                     config_file;     // relative or absolute file path/name for the infer config file to load
        uint32_t                                        interval;        // frame interval to infer on
    } PrimaryTisInferCompConfig;

    typedef struct SecondaryTisInferCompConfig
    {
        std::string                                     config_file;     // relative or absolute file path/name for the infer config file to load
        std::string                                     infer_on_tis;    // unique name of the Primary or Secondary TIS to infer on
        uint32_t                                        interval;        // frame interval to infer on
    } SecondaryTisInferCompConfig;

    typedef struct InferCompConfig
    {
        InferCompType                                   type;
        union
        {
            PrimaryGieInferCompConfig                   primary_gie_config;
            SecondaryGieInferCompConfig                 secondary_gie_config;
            PrimaryTisInferCompConfig                   primary_tis_config;
            SecondaryTisInferCompConfig                 secondary_tis_config;
        };
    } InferCompConfig;

    void logValidInferCompType();
    int convertStrToInferCompType(const std::string type_str, InferCompType& type);
    int convertInferCompTypeToStr(const InferCompType type, std::string& type_str);
    int parseInferCompConfigFromNode(const YAML::Node& node, InferCompConfig& config);
    int dumpInferCompConfigToNode(const InferCompConfig& config, YAML::Node& node);
    extern std::map<std::string, InferCompType> gStrToInferCompType;
    extern std::map<InferCompType, std::string> gInferCompTypeToStr;

} // namespace DslPipelineServer