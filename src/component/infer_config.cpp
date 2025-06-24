/********************************************
// Filename: infer_config.cpp
// Created by zhaojiadi on 2023/4/29
// Description:

********************************************/
#include <fstream>
#include <sstream>
#include "common/logger.h"
#include "component/infer_config.h"

namespace YAML
{

    template <>
    struct convert<DslPipelineServer::PrimaryGieInferCompConfig>
    {
        using PrimaryGieInferCompConfig = DslPipelineServer::PrimaryGieInferCompConfig;

        static Node encode(const PrimaryGieInferCompConfig& rhs)
        {
            Node node;
            node["config_file"] = rhs.config_file;
            node["engine_file"] = rhs.engine_file;
            node["interval"] = rhs.interval;
            return node;
        }

        static bool decode(const Node& node, PrimaryGieInferCompConfig& rhs)
        {
            if (!node.IsMap())
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "expect PrimaryGieInferCompConfig node type is map:{}, but get {}", 
                    int(NodeType::Map), int(node.Type()));
                return false;
            }

            rhs.config_file = node["config_file"].as<std::string>();
            rhs.engine_file = node["engine_file"].as<std::string>();
            rhs.interval = node["interval"].as<uint32_t>();
            return true;
        }
    };

    template <>
    struct convert<DslPipelineServer::SecondaryGieInferCompConfig>
    {
        using SecondaryGieInferCompConfig = DslPipelineServer::SecondaryGieInferCompConfig;

        static Node encode(const SecondaryGieInferCompConfig& rhs)
        {
            Node node;
            node["config_file"] = rhs.config_file;
            node["engine_file"] = rhs.engine_file;
            node["infer_on_gie"] = rhs.infer_on_gie;
            node["interval"] = rhs.interval;
            return node;
        }

        static bool decode(const Node& node, SecondaryGieInferCompConfig& rhs)
        {
            if (!node.IsMap())
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "expect SecondaryGieInferCompConfig node type is map:{}, but get {}", 
                    int(NodeType::Map), int(node.Type()));
                return false;
            }

            rhs.config_file = node["config_file"].as<std::string>();
            rhs.engine_file = node["engine_file"].as<std::string>();
            rhs.infer_on_gie = node["infer_on_gie"].as<std::string>();
            rhs.interval = node["interval"].as<uint32_t>();
            return true;
        }
    };

    template <>
    struct convert<DslPipelineServer::PrimaryTisInferCompConfig>
    {
        using PrimaryTisInferCompConfig = DslPipelineServer::PrimaryTisInferCompConfig;

        static Node encode(const PrimaryTisInferCompConfig& rhs)
        {
            Node node;
            node["config_file"] = rhs.config_file;
            node["interval"] = rhs.interval;
            return node;
        }

        static bool decode(const Node& node, PrimaryTisInferCompConfig& rhs)
        {
            if (!node.IsMap())
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "expect PrimaryTisInferCompConfig node type is map:{}, but get {}", 
                    int(NodeType::Map), int(node.Type()));
                return false;
            }

            rhs.config_file = node["config_file"].as<std::string>();
            rhs.interval = node["interval"].as<uint32_t>();
            return true;
        }
    };

    template <>
    struct convert<DslPipelineServer::SecondaryTisInferCompConfig>
    {
        using SecondaryTisInferCompConfig = DslPipelineServer::SecondaryTisInferCompConfig;

        static Node encode(const SecondaryTisInferCompConfig& rhs)
        {
            Node node;
            node["config_file"] = rhs.config_file;
            node["infer_on_tis"] = rhs.infer_on_tis;
            node["interval"] = rhs.interval;
            return node;
        }

        static bool decode(const Node& node, SecondaryTisInferCompConfig& rhs)
        {
            if (!node.IsMap())
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "expect SecondaryTisInferCompConfig node type is map:{}, but get {}", 
                    int(NodeType::Map), int(node.Type()));
                return false;
            }

            rhs.config_file = node["config_file"].as<std::string>();
            rhs.infer_on_tis = node["infer_on_tis"].as<std::string>();
            rhs.interval = node["interval"].as<uint32_t>();
            return true;
        }
    };

    template <>
    struct convert<DslPipelineServer::InferCompConfig>
    {
        using InferCompConfig = DslPipelineServer::InferCompConfig;
        using PrimaryGieInferCompConfig = DslPipelineServer::PrimaryGieInferCompConfig;
        using SecondaryGieInferCompConfig = DslPipelineServer::SecondaryGieInferCompConfig;
        using PrimaryTisInferCompConfig = DslPipelineServer::PrimaryTisInferCompConfig;
        using SecondaryTisInferCompConfig = DslPipelineServer::SecondaryTisInferCompConfig;

        static Node encode(const InferCompConfig& rhs)
        {
            Node node;
            node["type"] = rhs.type;
            switch (rhs.type)
            {
                case DslPipelineServer::PRIMARY_GIE_INFER_COMP_TYPE:
                {
                    node["config"] = rhs.primary_gie_config;
                    break;
                }
                case DslPipelineServer::SECONDARY_GIE_INFER_COMP_TYPE:
                {
                    node["config"] = rhs.secondary_gie_config;
                    break;
                }
                case DslPipelineServer::PRIMARY_TIS_INFER_COMP_TYPE:
                {
                    node["config"] = rhs.primary_tis_config;
                    break;
                }
                case DslPipelineServer::SECONDARY_TIS_INFER_COMP_TYPE:
                {
                    node["config"] = rhs.secondary_tis_config;
                    break;
                }
                default:
                {
                    PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "invalid infer component type: {}", int(rhs.type));
                    break;
                }
            }
            return node;
        }

        static bool decode(const Node& node, InferCompConfig& rhs)
        {
            if (!node.IsMap())
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "expect InferCompConfig node type is map:{}, but get {}", 
                    int(NodeType::Map), int(node.Type()));
                return false;
            }
            auto type_str = node["type"].as<std::string>();
            if (gStrToInferCompType.end() == gStrToInferCompType.find(type_str))
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "invalid infer component type {}, please check", type_str);
                return false;
            }
            auto type = gStrToInferCompType[type_str];
            rhs.type = type;
            switch (rhs.type)
            {
                case DslPipelineServer::PRIMARY_GIE_INFER_COMP_TYPE:
                {
                    rhs.primary_gie_config = node["config"].as<PrimaryGieInferCompConfig>();
                    break;
                }
                case DslPipelineServer::SECONDARY_GIE_INFER_COMP_TYPE:
                {
                    rhs.secondary_gie_config = node["config"].as<SecondaryGieInferCompConfig>();
                    break;
                }
                case DslPipelineServer::PRIMARY_TIS_INFER_COMP_TYPE:
                {
                    rhs.primary_tis_config = node["config"].as<PrimaryTisInferCompConfig>();
                    break;
                }
                case DslPipelineServer::SECONDARY_TIS_INFER_COMP_TYPE:
                {
                    rhs.secondary_tis_config = node["config"].as<SecondaryTisInferCompConfig>();
                    break;
                }
                default:
                {
                    PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "invalid infer component type: {}", int(rhs.type));
                    return false;
                }
            }
            return true;
        }
    };

} // namespace YAML

namespace DslPipelineServer
{

    // string to infer component type map
    std::map<std::string, InferCompType> gStrToInferCompType = {
        {"PRIMARY_GIE",                         PRIMARY_GIE_INFER_COMP_TYPE},
        {"SECONDARY_GIE",                       SECONDARY_GIE_INFER_COMP_TYPE},
        {"PRIMARY_TIS",                         PRIMARY_TIS_INFER_COMP_TYPE},
        {"SECONDARY_TIS",                       SECONDARY_TIS_INFER_COMP_TYPE},
    };

    // infer component type to string map
    std::map<InferCompType, std::string> gInferCompTypeToStr = {
        {PRIMARY_GIE_INFER_COMP_TYPE,           "PRIMARY_GIE"},
        {SECONDARY_GIE_INFER_COMP_TYPE,         "SECONDARY_GIE"},
        {PRIMARY_TIS_INFER_COMP_TYPE,           "PRIMARY_TIS"},
        {SECONDARY_TIS_INFER_COMP_TYPE,         "SECONDARY_TIS"},
    };

    void logValidInferCompType()
    {
        PIPELINE_LOG(PIPELINE_LOG_LEVEL_INFO, "valid infer component type as follows:");
        for (auto it = gInferCompTypeToStr.begin(); it != gInferCompTypeToStr.end(); it++)
        {
            auto type = it->first;
            auto type_str = it->second;
            PIPELINE_LOG(PIPELINE_LOG_LEVEL_INFO, "{} ----> {}", type, type_str);
        }
        return;
    }

    int convertStrToInferCompType(const std::string type_str, InferCompType& type)
    {
        if (gStrToInferCompType.end() == gStrToInferCompType.find(type_str))
            return -1;

        type = gStrToInferCompType[type_str];
        return 0;
    }

    int convertInferCompTypeToStr(const InferCompType type, std::string& type_str)
    {
        if (gInferCompTypeToStr.end() == gInferCompTypeToStr.find(type))
            return -1;

        type_str = gInferCompTypeToStr[type];
        return 0;
    }

    int parseInferCompConfigFromNode(const YAML::Node& node, InferCompConfig& config)
    {
        try
        {
            config = node["config"].as<InferCompConfig>();
        }
        catch (const std::exception &e)
        {
            PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "parse infer component node error:\n {}", e.what());
            return -1;
        }
        return 0;
    }

    int dumpInferCompConfigToNode(const InferCompConfig& config, YAML::Node& node)
    {
        try
        {
            node["config"] = config;
        }
        catch (const std::exception &e)
        {
            PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "dump infer component config error:\n {}", e.what());
            return -1;
        }
        return 0;
    }

} // namespace DslPipelineServer