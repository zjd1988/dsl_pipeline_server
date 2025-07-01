/********************************************
// Filename: source_config.cpp
// Created by zhaojiadi on 2023/4/29
// Description:

********************************************/
#include <fstream>
#include <sstream>
#include "common/logger.h"
#include "component/source_config.h"

namespace YAML
{

    template <>
    struct convert<DslPipelineServer::AppSourceCompConfig>
    {
        using AppSourceCompConfig = DslPipelineServer::AppSourceCompConfig;

        static Node encode(const AppSourceCompConfig& rhs)
        {
            Node node;
            node["is_live"] = rhs.is_live;
            node["buffer_in_format"] = rhs.buffer_in_format;
            node["width"] = rhs.width;
            node["height"] = rhs.height;
            node["fps_n"] = rhs.fps_n;
            node["fps_d"] = rhs.fps_d;
            return node;
        }

        static bool decode(const Node& node, AppSourceCompConfig& rhs)
        {
            if (!node.IsMap())
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "expect AppSourceCompConfig node type is map:{}, but get {}", 
                    int(NodeType::Map), int(node.Type()));
                return false;
            }

            rhs.is_live = node["is_live"].as<bool>();
            rhs.buffer_in_format = node["buffer_in_format"].as<std::string>();
            rhs.width = node["width"].as<uint32_t>();
            rhs.height = node["height"].as<uint32_t>();
            rhs.fps_n = node["fps_n"].as<uint32_t>();
            rhs.fps_d = node["fps_d"].as<uint32_t>();
            return true;
        }
    };

    template <>
    struct convert<DslPipelineServer::CsiSourceCompConfig>
    {
        using CsiSourceCompConfig = DslPipelineServer::CsiSourceCompConfig;

        static Node encode(const CsiSourceCompConfig& rhs)
        {
            Node node;
            node["width"] = rhs.width;
            node["height"] = rhs.height;
            node["fps_n"] = rhs.fps_n;
            node["fps_d"] = rhs.fps_d;
            return node;
        }

        static bool decode(const Node& node, CsiSourceCompConfig& rhs)
        {
            if (!node.IsMap())
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "expect CsiSourceCompConfig node type is map:{}, but get {}", 
                    int(NodeType::Map), int(node.Type()));
                return false;
            }

            rhs.width = node["width"].as<uint32_t>();
            rhs.height = node["height"].as<uint32_t>();
            rhs.fps_n = node["fps_n"].as<uint32_t>();
            rhs.fps_d = node["fps_d"].as<uint32_t>();
            return true;
        }
    };

    template <>
    struct convert<DslPipelineServer::V4l2SourceCompConfig>
    {
        using V4l2SourceCompConfig = DslPipelineServer::V4l2SourceCompConfig;

        static Node encode(const V4l2SourceCompConfig& rhs)
        {
            Node node;
            node["device_location"] = rhs.device_location;
            return node;
        }

        static bool decode(const Node& node, V4l2SourceCompConfig& rhs)
        {
            if (!node.IsMap())
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "expect V4l2SourceCompConfig node type is map:{}, but get {}", 
                    int(NodeType::Map), int(node.Type()));
                return false;
            }

            rhs.device_location = node["device_location"].as<std::string>();
            return true;
        }
    };

    template <>
    struct convert<DslPipelineServer::UriSourceCompConfig>
    {
        using UriSourceCompConfig = DslPipelineServer::UriSourceCompConfig;

        static Node encode(const UriSourceCompConfig& rhs)
        {
            Node node;
            node["uri"] = rhs.uri;
            node["is_live"] = rhs.is_live;
            node["skip_frames"] = rhs.skip_frames;
            node["drop_frame_interval"] = rhs.drop_frame_interval;
            return node;
        }

        static bool decode(const Node& node, UriSourceCompConfig& rhs)
        {
            if (!node.IsMap())
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "expect UriSourceCompConfig node type is map:{}, but get {}", 
                    int(NodeType::Map), int(node.Type()));
                return false;
            }

            rhs.uri = node["uri"].as<std::string>();
            rhs.is_live = node["is_live"].as<bool>();
            rhs.skip_frames = node["skip_frames"].as<uint32_t>();
            rhs.drop_frame_interval = node["drop_frame_interval"].as<uint32_t>();
            return true;
        }
    };

    template <>
    struct convert<DslPipelineServer::FileSourceCompConfig>
    {
        using FileSourceCompConfig = DslPipelineServer::FileSourceCompConfig;

        static Node encode(const FileSourceCompConfig& rhs)
        {
            Node node;
            node["file_path"] = rhs.file_path;
            node["repeat_enabled"] = rhs.repeat_enabled;
            return node;
        }

        static bool decode(const Node& node, FileSourceCompConfig& rhs)
        {
            if (!node.IsMap())
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "expect FileSourceCompConfig node type is map:{}, but get {}", 
                    int(NodeType::Map), int(node.Type()));
                return false;
            }

            rhs.file_path = node["file_path"].as<std::string>();
            rhs.repeat_enabled = node["repeat_enabled"].as<bool>();
            return true;
        }
    };

    template <>
    struct convert<DslPipelineServer::RtspSourceCompConfig>
    {
        using RtspSourceCompConfig = DslPipelineServer::RtspSourceCompConfig;

        static Node encode(const RtspSourceCompConfig& rhs)
        {
            Node node;
            node["uri"] = rhs.uri;
            node["protocol"] = rhs.protocol;
            node["skip_frames"] = rhs.skip_frames;
            node["drop_frame_interval"] = rhs.drop_frame_interval;
            node["latency"] = rhs.latency;
            node["timeout"] = rhs.timeout;
            return node;
        }

        static bool decode(const Node& node, RtspSourceCompConfig& rhs)
        {
            if (!node.IsMap())
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "expect RtspSourceCompConfig node type is map:{}, but get {}", 
                    int(NodeType::Map), int(node.Type()));
                return false;
            }

            rhs.uri = node["uri"].as<std::string>();
            rhs.protocol = node["protocol"].as<uint32_t>();
            rhs.skip_frames = node["skip_frames"].as<uint32_t>();
            rhs.drop_frame_interval = node["drop_frame_interval"].as<uint32_t>();
            rhs.latency = node["latency"].as<uint32_t>();
            rhs.timeout = node["timeout"].as<uint32_t>();
            return true;
        }
    };

    template <>
    struct convert<DslPipelineServer::SourceCompConfig>
    {
        using SourceCompConfig = DslPipelineServer::SourceCompConfig;
        using AppSourceCompConfig = DslPipelineServer::AppSourceCompConfig;
        using CsiSourceCompConfig = DslPipelineServer::CsiSourceCompConfig;
        using V4l2SourceCompConfig = DslPipelineServer::V4l2SourceCompConfig;
        using UriSourceCompConfig = DslPipelineServer::UriSourceCompConfig;
        using FileSourceCompConfig = DslPipelineServer::FileSourceCompConfig;
        using RtspSourceCompConfig = DslPipelineServer::RtspSourceCompConfig;

        static Node encode(const SourceCompConfig& rhs)
        {
            std::string source_type_str;
            if (0 != DslPipelineServer::convertSourceCompTypeToStr(rhs.source_type, source_type_str))
            {
                std::string err_str = fmt::format("component: {} have invalid source component type: {}", 
                    rhs.comp_name, int(rhs.source_type));
                throw DslPipelineServer::ParseException(err_str);
            }
            Node node;
            node["type"] = source_type_str;
            switch (rhs.source_type)
            {
                case DslPipelineServer::APP_SOURCE_COMP_TYPE:
                {
                    node = rhs.app_config;
                    break;
                }
                case DslPipelineServer::CSI_SOURCE_COMP_TYPE:
                {
                    node = rhs.csi_config;
                    break;
                }
                case DslPipelineServer::V4L2_SOURCE_COMP_TYPE:
                {
                    node = rhs.v4l2_config;
                    break;
                }
                case DslPipelineServer::URI_SOURCE_COMP_TYPE:
                {
                    node = rhs.uri_config;
                    break;
                }
                case DslPipelineServer::FILE_SOURCE_COMP_TYPE:
                {
                    node = rhs.file_config;
                    break;
                }
                case DslPipelineServer::RTSP_SOURCE_COMP_TYPE:
                {
                    node = rhs.rtsp_config;
                    break;
                }
                default:
                {
                    std::string err_str = fmt::format("component: {} have invalid source component type: {}", 
                        rhs.comp_name, int(rhs.source_type));
                    throw DslPipelineServer::ParseException(err_str);
                }
            }
            return node;
        }

        static bool decode(const Node& node, SourceCompConfig& rhs)
        {
            auto comp_name = rhs.comp_name;
            if (!node.IsMap())
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "expect SourceCompConfig node type is map:{}, but get {}", 
                    int(NodeType::Map), int(node.Type()));
                return false;
            }
            auto source_type_str = node["type"].as<std::string>();
            DslPipelineServer::SourceCompType source_type;
            if (0 != DslPipelineServer::convertStrToSourceCompType(source_type_str, source_type))
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "component: {} have invalid source component type: {}", 
                    comp_name, source_type_str);
                return false;
            }
            rhs.source_type = source_type;
            switch (rhs.source_type)
            {
                case DslPipelineServer::APP_SOURCE_COMP_TYPE:
                {
                    rhs.app_config = node.as<AppSourceCompConfig>();
                    break;
                }
                case DslPipelineServer::CSI_SOURCE_COMP_TYPE:
                {
                    rhs.csi_config = node.as<CsiSourceCompConfig>();
                    break;
                }
                case DslPipelineServer::V4L2_SOURCE_COMP_TYPE:
                {
                    rhs.v4l2_config = node.as<V4l2SourceCompConfig>();
                    break;
                }
                case DslPipelineServer::URI_SOURCE_COMP_TYPE:
                {
                    rhs.uri_config = node.as<UriSourceCompConfig>();
                    break;
                }
                case DslPipelineServer::FILE_SOURCE_COMP_TYPE:
                {
                    rhs.file_config = node.as<FileSourceCompConfig>();
                    break;
                }
                case DslPipelineServer::RTSP_SOURCE_COMP_TYPE:
                {
                    rhs.rtsp_config = node.as<RtspSourceCompConfig>();
                    break;
                }
                default:
                {
                    PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "component: {} invalid source component type: {}", 
                        comp_name, source_type_str);
                    return false;
                }
            }
            return true;
        }
    };

} // namespace YAML

namespace DslPipelineServer
{

    // string to source component type map
    std::map<std::string, SourceCompType> gStrToSourceCompType = {
        {"APP",                                 APP_SOURCE_COMP_TYPE},
        {"CSI",                                 CSI_SOURCE_COMP_TYPE},
        {"V4L2",                                V4L2_SOURCE_COMP_TYPE},
        {"URI",                                 URI_SOURCE_COMP_TYPE},
        {"FILE",                                FILE_SOURCE_COMP_TYPE},
        {"RTSP",                                RTSP_SOURCE_COMP_TYPE},
    };

    // source component type to string map
    std::map<SourceCompType, std::string> gSourceCompTypeToStr = {
        {APP_SOURCE_COMP_TYPE,                  "APP"},
        {CSI_SOURCE_COMP_TYPE,                  "CSI"},
        {V4L2_SOURCE_COMP_TYPE,                 "V4L2"},
        {URI_SOURCE_COMP_TYPE,                  "URI"},
        {FILE_SOURCE_COMP_TYPE,                 "FILE"},
        {RTSP_SOURCE_COMP_TYPE,                 "RTSP"},
    };

    void logValidSourceCompType()
    {
        PIPELINE_LOG(PIPELINE_LOG_LEVEL_INFO, "valid source component type as follows:");
        for (auto it = gSourceCompTypeToStr.begin(); it != gSourceCompTypeToStr.end(); it++)
        {
            auto type = it->first;
            auto type_str = it->second;
            PIPELINE_LOG(PIPELINE_LOG_LEVEL_INFO, "{} ----> {}", int(type), type_str);
        }
        return;
    }

    int convertStrToSourceCompType(const std::string type_str, SourceCompType& type)
    {
        if (gStrToSourceCompType.end() == gStrToSourceCompType.find(type_str))
            return -1;

        type = gStrToSourceCompType[type_str];
        return 0;
    }

    int convertSourceCompTypeToStr(const SourceCompType type, std::string& type_str)
    {
        if (gSourceCompTypeToStr.end() == gSourceCompTypeToStr.find(type))
            return -1;

        type_str = gSourceCompTypeToStr[type];
        return 0;
    }

    void parseSourceCompConfigFromNode(const YAML::Node& node, SourceCompConfig& config)
    {
        config = node.as<SourceCompConfig>();
        return;
    }

    void dumpSourceCompConfigToNode(const SourceCompConfig& config, YAML::Node& node)
    {

        node = config;
        return;
    }

} // namespace DslPipelineServer