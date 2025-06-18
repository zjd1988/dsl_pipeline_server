/********************************************
// Filename: pipeline_config.cpp
// Created by zhaojiadi on 2023/4/29
// Description:

********************************************/
#include <fstream>
#include <sstream>
#include <yaml-cpp/yaml.h>
#include "common/pipeline_config.h"

namespace DslPipelineServer
{

    // string to component type map
    std::map<std::string, ComponentType> gStrToComponentType = {
        {"SOURCE",                              SOURCE_COMPONENT_TYPE},
        {"PREPROCESS",                          PREPROCESS_COMPONENT_TYPE},
        {"INFER",                               INFER_COMPONENT_TYPE},
        {"TRACKER",                             TRACKER_COMPONENT_TYPE},
        {"TILER",                               TILER_COMPONENT_TYPE},
        {"OSD",                                 OSD_COMPONENT_TYPE},
        {"SINK",                                SINK_COMPONENT_TYPE},
        {"TEE",                                 TEE_COMPONENT_TYPE},
        {"BRANCH",                              BRANCH_COMPONENT_TYPE},
        {"REMUXER",                             REMUXER_COMPONENT_TYPE},
        {"PPH",                                 PPH_COMPONENT_TYPE},
    };

    // component type to string map
    std::map<ComponentType, std::string> gComponentTypeToStr = {
        {SOURCE_COMPONENT_TYPE,                 "SOURCE"},
        {PREPROCESS_COMPONENT_TYPE,             "PREPROCESS"},
        {INFER_COMPONENT_TYPE,                  "INFER"},
        {TRACKER_COMPONENT_TYPE,                "TRACKER"},
        {TILER_COMPONENT_TYPE,                  "TILER"},
        {OSD_COMPONENT_TYPE,                    "OSD"},
        {SINK_COMPONENT_TYPE,                   "SINK"},
        {TEE_COMPONENT_TYPE,                    "TEE"},
        {BRANCH_COMPONENT_TYPE,                 "BRANCH"},
        {REMUXER_COMPONENT_TYPE,                "REMUXER"},
        {PPH_COMPONENT_TYPE,                    "PPH"},
    };

    int convertStrToComponentType(const std::string type_str, ComponentType& type)
    {
        if (gStrToComponentType.end() == gStrToComponentType.find(type_str))
            return -1;

        type = gStrToComponentType[type_str];
        return 0;
    }

    int convertComponentTypeToStr(const ComponentType type, std::string& type_str)
    {
        if (gComponentTypeToStr.end() == gComponentTypeToStr.find(type))
            return -1;

        type_str = gComponentTypeToStr[type];
        return 0;
    }

    int parsePipelineConfigFromStr(const std::string& config_str, PipelineConfig& config)
    {
        try
        {
            auto config_node = YAML::Load(config_str);
            config = config_node.as<PipelineConfig>();
        }
        catch (const std::exception &e)
        {
            PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "parse config str {} error:\n {}", config_str, e.what());
            return -1;
        }
        return 0;
    }

    int parsePipelineConfigFromFile(const std::string& config_file, PipelineConfig& config)
    {
        try
        {
            std::ifstream file_stream(config_file);
            if (!file_stream.is_open())
            {
                std::cout << "open model config file: " << config_file << " fail" << std::endl;
                return -1;
            }
            std::stringstream file_data;
            file_data << file_stream.rdbuf();
            auto config_node = YAML::Load(file_data.str());
            config = config_node.as<PipelineConfig>();
        }
        catch (const std::exception &e)
        {
            PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "parse config file {} error:\n {}", config_file, e.what());
            return -1;
        }
        return 0;
    }

} // namespace DslPipelineServer
