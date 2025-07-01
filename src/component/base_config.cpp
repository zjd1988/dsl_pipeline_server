/********************************************
// Filename: base_config.cpp
// Created by zhaojiadi on 2023/4/29
// Description:

********************************************/
#include <fstream>
#include <sstream>
#include "common/logger.h"
#include "component/base_config.h"

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

    void logValidPipelineCompType()
    {
        PIPELINE_LOG(PIPELINE_LOG_LEVEL_INFO, "valid pipeline component type as follows:");
        for (auto it = gComponentTypeToStr.begin(); it != gComponentTypeToStr.end(); it++)
        {
            auto type = it->first;
            auto type_str = it->second;
            PIPELINE_LOG(PIPELINE_LOG_LEVEL_INFO, "{} ----> {}", int(type), type_str);
        }
        return;
    }

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

} // namespace DslPipelineServer