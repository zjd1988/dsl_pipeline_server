/********************************************
// Filename: pipeline_config.cpp
// Created by zhaojiadi on 2023/4/29
// Description:

********************************************/
#include <fstream>
#include <sstream>
#include <yaml-cpp/yaml.h>
#include "common/pipeline_config.h"

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
            int ret = 0;
            switch (rhs.type)
            {
                case DslPipelineServer::SOURCE_COMPONENT_TYPE:
                {
                    ret = dumpSourceCompConfigToNode(rhs.source_config, node);
                    break;
                }
                case DslPipelineServer::INFER_COMPONENT_TYPE:
                {
                    ret = dumpInferCompConfigToNode(rhs.infer_config, node);
                    break;
                }
                case DslPipelineServer::TRACKER_COMPONENT_TYPE:
                {
                    ret = dumpTrackerCompConfigToNode(rhs.tracker_config, node);
                    break;
                }
                case DslPipelineServer::OSD_COMPONENT_TYPE:
                {
                    ret = dumpOsdCompConfigToNode(rhs.osd_config, node);
                    break;
                }
                case DslPipelineServer::SINK_COMPONENT_TYPE:
                {
                    ret = dumpSinkCompConfigToNode(rhs.sink_config, node);
                    break;
                }
                default:
                {
                    PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "invalid component type: {}", int(rhs.type));
                    ret = -1;
                    break;
                }
            }
            return node;
        }

        static bool decode(const Node& node, ComponentConfig& rhs)
        {
            if (!node.IsMap())
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "expect ComponentConfig node type is map:{}, but get {}", 
                    int(NodeType::Map), int(node.Type()));
                return false;
            }

            rhs.name = node["name"].as<std::string>();
            auto type_str = node["type"].as<std::string>();
            if (gStrToComponentType.end() == gStrToComponentType.find(type_str))
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "invalid component type {}, please check", type_str);
                return false;
            }
            auto type = gStrToComponentType[type_str];
            rhs.type = type;
            int ret = 0;
            switch (type)
            {
                case DslPipelineServer::SOURCE_COMPONENT_TYPE:
                {
                    ret = parseSourceCompConfigFromNode(node, rhs.source_config);
                    break;
                }
                case DslPipelineServer::INFER_COMPONENT_TYPE:
                {
                    ret = parseInferCompConfigFromNode(node, rhs.infer_config);
                    break;
                }
                case DslPipelineServer::TRACKER_COMPONENT_TYPE:
                {
                    ret = parseTrackerCompConfigFromNode(node, rhs.tracker_config);
                    break;
                }
                case DslPipelineServer::OSD_COMPONENT_TYPE:
                {
                    ret = parseOsdCompConfigFromNode(node, rhs.osd_config);
                    break;
                }
                case DslPipelineServer::SINK_COMPONENT_TYPE:
                {
                    ret = parseSinkCompConfigFromNode(node, rhs.sink_config);
                    break;
                }
                default:
                {
                    PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "invalid component type: {}", int(rhs.type));
                    ret = -1;
                    break;
                }
            }
            return (ret == 0);
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
            if (!node.IsMap())
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "expect PipelineConfig node type is map:{}, but get {}", 
                    int(NodeType::Map), int(node.Type()));
                return false;
            }
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
            PIPELINE_LOG(PIPELINE_LOG_LEVEL_INFO, "{} ----> {}", type, type_str);
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
