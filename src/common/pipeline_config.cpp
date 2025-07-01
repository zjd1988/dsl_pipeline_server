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
    struct convert<DslPipelineServer::PipelineConfig>
    {
        using PipelineConfig = DslPipelineServer::PipelineConfig;
        using BaseCompConfig = DslPipelineServer::BaseCompConfig;
        using SourceCompConfig = DslPipelineServer::SourceCompConfig;
        using SinkCompConfig = DslPipelineServer::SinkCompConfig;
        using InferCompConfig = DslPipelineServer::InferCompConfig;
        using TrackerCompConfig = DslPipelineServer::TrackerCompConfig;
        using OsdCompConfig = DslPipelineServer::OsdCompConfig;

        static Node encode(const PipelineConfig& rhs)
        {
            Node node;
            node["components"] = YAML::Node();
            for (size_t index = 0; index < rhs.component_configs.size(); index++)
            {
                auto& config = rhs.component_configs[index];
                std::string comp_type_str;
                if (0 != convertComponentTypeToStr(config->comp_type, comp_type_str))
                {
                    PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "{} has invalid component type: {}", 
                        config->comp_name, comp_type_str);
                    continue;
                }
                Node config_node;
                switch (config->comp_type)
                {
                    case DslPipelineServer::SOURCE_COMPONENT_TYPE:
                    {
                        dumpSourceCompConfigToNode(*(SourceCompConfig*)config.get(), config_node);
                        break;
                    }
                    case DslPipelineServer::INFER_COMPONENT_TYPE:
                    {
                        dumpInferCompConfigToNode(*(InferCompConfig*)config.get(), config_node);
                        break;
                    }
                    case DslPipelineServer::TRACKER_COMPONENT_TYPE:
                    {
                        dumpTrackerCompConfigToNode(*(TrackerCompConfig*)config.get(), config_node);
                        break;
                    }
                    case DslPipelineServer::OSD_COMPONENT_TYPE:
                    {
                        dumpOsdCompConfigToNode(*(OsdCompConfig*)config.get(), config_node);
                        break;
                    }
                    case DslPipelineServer::SINK_COMPONENT_TYPE:
                    {
                        dumpSinkCompConfigToNode(*(SinkCompConfig*)config.get(), config_node);
                        break;
                    }
                    default:
                    {
                        PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "{} has invalid component type: {}", 
                            config->comp_name, int(config->comp_type));
                        break;
                    }
                }
                Node component_node;
                component_node["name"] = config->comp_name;
                component_node["type"] = comp_type_str;
                component_node["config"] = config_node;
                node["components"].push_back(component_node);
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
                    if (!component_node.IsMap())
                    {
                        PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "expect ComponentConfig node type is map:{}, but get {}", 
                            int(NodeType::Map), int(component_node.Type()));
                        return false;
                    }
                    std::string name = component_node["name"].as<std::string>();
                    std::string type_str = component_node["type"].as<std::string>();
                    DslPipelineServer::ComponentType type;
                    if (0 != convertStrToComponentType(type_str, type))
                    {
                        PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "component {} has invalid component type: {}", name, type_str);
                        return false;
                    }
                    int ret = 0;
                    std::shared_ptr<BaseCompConfig> config;
                    config->comp_name = name;
                    config->comp_type = type;
                    auto& config_node = component_node["config"];
                    switch (type)
                    {
                        case DslPipelineServer::SOURCE_COMPONENT_TYPE:
                        {
                            config.reset(new SourceCompConfig());
                            parseSourceCompConfigFromNode(config_node, *(SourceCompConfig*)config.get());
                            break;
                        }
                        case DslPipelineServer::INFER_COMPONENT_TYPE:
                        {
                            parseInferCompConfigFromNode(config_node, *(InferCompConfig*)config.get());
                            break;
                        }
                        case DslPipelineServer::TRACKER_COMPONENT_TYPE:
                        {
                            parseTrackerCompConfigFromNode(config_node, *(TrackerCompConfig*)config.get());
                            break;
                        }
                        case DslPipelineServer::OSD_COMPONENT_TYPE:
                        {
                            parseOsdCompConfigFromNode(config_node, *(OsdCompConfig*)config.get());
                            break;
                        }
                        case DslPipelineServer::SINK_COMPONENT_TYPE:
                        {
                            parseSinkCompConfigFromNode(config_node, *(SinkCompConfig*)config.get());
                            break;
                        }
                        default:
                        {
                            PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "current not support component type: {}", type_str);
                            break;
                        }
                    }
                    if (0 == ret)
                        rhs.component_configs.push_back(config);
                    else
                        PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "parse component: {} fail", name);
                }
            }
            return true;
        }
    };

} // namespace YAML

namespace DslPipelineServer
{

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
