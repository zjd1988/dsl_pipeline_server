/********************************************
// Filename: base_config.h
// Created by zhaojiadi on 2023/4/29
// Description:

********************************************/
#pragma once
#include <string>

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

    typedef struct BaseCompConfig
    {
        std::string                                     comp_name;
        ComponentType                                   comp_type;
    } BaseCompConfig;

    void logValidPipelineCompType();
    int convertStrToComponentType(const std::string type_str, ComponentType& type);
    int convertComponentTypeToStr(const ComponentType type, std::string& type_str);
    extern std::map<std::string, ComponentType> gStrToComponentType;
    extern std::map<ComponentType, std::string> gComponentTypeToStr;

    class ParseException : public std::runtime_error
    {
    public:
        ParseException(const std::string& msg) : std::runtime_error(msg) {}
    };

} // namespace DslPipelineServer