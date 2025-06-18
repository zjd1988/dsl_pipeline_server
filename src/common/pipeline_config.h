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
        std::vector<std::string>                         component_names;
        std::map<std::string, ComponentConfig>           component_configs;
    } PipelineConfig;

    int convertStrToComponentType(const std::string type_str, ComponentType& type);
    int convertComponentTypeToStr(const ComponentType type, std::string& type_str);
    int parsePipelineConfigFromStr(const std::string& config_str, PipelineConfig& config);
    int parsePipelineConfigFromFile(const std::string& config_file, PipelineConfig& config);
    extern std::map<std::string, ComponentType> gStrToComponentType;
    extern std::map<ComponentType, std::string> gComponentTypeToStr;

} // namespace DslPipelineServer

namespace YAML
{

    template <>
    struct convert<DslPipelineServer::ComponentConfig>
    {
        using ComponentConfig = DslPipelineServer::ComponentConfig;
        using SourceCompConfig = DslPipelineServer::SourceCompConfig;
        using SinkCompConfig = DslPipelineServer::SinkCompConfig;
        using InferCompConfig = DslPipelineServer::InferCompConfig;
        using TrackerCompConfig = DslPipelineServer::TrackerCompConfig;
        using OsdCompConfig = DslPipelineServer::OsdCompConfig;

        static Node encode(const ComponentConfig& rhs)
        {
            Node node;
            node["name"] = rhs.name;
            node["type"] = rhs.type;
            switch (rhs.type)
            {
                case DslPipelineServer::SOURCE_COMPONENT_TYPE:
                {
                    node["config"] = rhs.source_config;
                    break;
                }
                case DslPipelineServer::INFER_COMPONENT_TYPE:
                {
                    node["config"] = rhs.infer_config;
                    break;
                }
                case DslPipelineServer::TRACKER_COMPONENT_TYPE:
                {
                    node["config"] = rhs.tracker_config;
                    break;
                }
                case DslPipelineServer::OSD_COMPONENT_TYPE:
                {
                    node["config"] = rhs.osd_config;
                    break;
                }
                case DslPipelineServer::SINK_COMPONENT_TYPE:
                {
                    node["config"] = rhs.sink_config;
                    break;
                }
                default:
                {
                    break;
                }
            }
            return node;
        }

        static bool decode(const Node& node, ComponentConfig& rhs)
        {
            if (!node.IsMap()) return false;
            
            rhs.name = node["name"].as<std::string>();
            auto type_str = node["type"].as<std::string>();
            if (gStrToComponentType.end() == gStrToComponentType.find(type_str))
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "invalid component type {}, please check", type_str);
                return false;
            }
            auto type = gStrToComponentType[type_str];
            rhs.type = type;
            switch (type)
            {
                case DslPipelineServer::SOURCE_COMPONENT_TYPE:
                {
                    rhs.source_config = node["config"].as<SourceCompConfig>();
                    break;
                }
                case DslPipelineServer::INFER_COMPONENT_TYPE:
                {
                    rhs.infer_config = node["config"].as<InferCompConfig>();
                    break;
                }
                case DslPipelineServer::TRACKER_COMPONENT_TYPE:
                {
                    rhs.tracker_config = node["config"].as<TrackerCompConfig>();
                    break;
                }
                case DslPipelineServer::OSD_COMPONENT_TYPE:
                {
                    rhs.osd_config = node["config"].as<OsdCompConfig>();
                    break;
                }
                case DslPipelineServer::SINK_COMPONENT_TYPE:
                {
                    rhs.sink_config = node["config"].as<SinkCompConfig>();
                    break;
                }
                default:
                {
                    return false;
                }
            }
            return true;
        }
    };

    template <>
    struct convert<DslPipelineServer::PipelineConfig>
    {
        using PipelineConfig = DslPipelineServer::PipelineConfig;
        using ComponentConfig = DslPipelineServer::ComponentConfig;

        static Node encode(const PipelineConfig& rhs)
        {
            Node node;
            node["components"] = YAML::Node();
            for (const auto& name : rhs.component_names)
            {
                if (rhs.component_configs.end() != rhs.component_configs.find(name))
                {
                    Node component_node = rhs.component_configs[name];
                    node["components"].push_back(component_node);
                }
            }
            return node;
        }

        static bool decode(const Node& node, PipelineConfig& rhs)
        {
            if (!node.IsMap()) return false;
            if (node["components"] && node["components"].IsSequence())
            {
                for (const auto& component_node : node["components"])
                {
                    auto component_config = component_node.as<ComponentConfig>();
                    auto name = component_config.name;
                    // check dumplicate component
                    if (rhs.component_configs.end() != rhs.component_configs.find(name))
                    {
                        PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "duplicate component {}, please check", name);
                        return false;
                    }
                    rhs.component_configs[name] = component_config;
                    rhs.component_names.emplace_back(name);
                }
            }

            return true;
        }
    };

} // namespace YAML