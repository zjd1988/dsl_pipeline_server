/********************************************
// Filename: sink_config.cpp
// Created by zhaojiadi on 2023/4/29
// Description:

********************************************/
#include <fstream>
#include <sstream>
#include "common/logger.h"
#include "component/sink_config.h"

namespace YAML
{

    template <>
    struct convert<DslPipelineServer::AppSinkComConfig>
    {
        using AppSinkComConfig = DslPipelineServer::AppSinkComConfig;

        static Node encode(const AppSinkComConfig& rhs)
        {
            Node node;
            node["data_type"] = rhs.data_type;
            return node;
        }

        static bool decode(const Node& node, AppSinkComConfig& rhs)
        {
            if (!node.IsMap())
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "expect AppSinkComConfig node type is map:{}, but get {}", 
                    int(NodeType::Map), int(node.Type()));
                return false;
            }

            rhs.data_type = node["data_type"].as<uint32_t>();
            return true;
        }
    };

    template <>
    struct convert<DslPipelineServer::V4l2SinkCompConfig>
    {
        using V4l2SinkCompConfig = DslPipelineServer::V4l2SinkCompConfig;

        static Node encode(const V4l2SinkCompConfig& rhs)
        {
            Node node;
            node["device_location"] = rhs.device_location;
            return node;
        }

        static bool decode(const Node& node, V4l2SinkCompConfig& rhs)
        {
            if (!node.IsMap())
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "expect V4l2SinkCompConfig node type is map:{}, but get {}", 
                    int(NodeType::Map), int(node.Type()));
                return false;
            }

            rhs.device_location = node["device_location"].as<std::string>();
            return true;
        }
    };

    template <>
    struct convert<DslPipelineServer::FileSinkCompConfig>
    {
        using FileSinkCompConfig = DslPipelineServer::FileSinkCompConfig;

        static Node encode(const FileSinkCompConfig& rhs)
        {
            Node node;
            node["file_path"] = rhs.file_path;
            node["encoder"] = rhs.encoder;
            node["container"] = rhs.container;
            node["bitrate"] = rhs.bitrate;
            node["iframe_interval"] = rhs.iframe_interval;
            return node;
        }

        static bool decode(const Node& node, FileSinkCompConfig& rhs)
        {
            if (!node.IsMap())
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "expect FileSinkCompConfig node type is map:{}, but get {}", 
                    int(NodeType::Map), int(node.Type()));
                return false;
            }

            rhs.file_path = node["file_path"].as<std::string>();
            rhs.encoder = node["encoder"].as<uint32_t>();
            rhs.container = node["container"].as<uint32_t>();
            rhs.bitrate = node["bitrate"].as<uint32_t>();
            rhs.iframe_interval = node["iframe_interval"].as<uint32_t>();
            return true;
        }
    };

    template <>
    struct convert<DslPipelineServer::RecordSinkCompConfig>
    {
        using RecordSinkCompConfig = DslPipelineServer::RecordSinkCompConfig;

        static Node encode(const RecordSinkCompConfig& rhs)
        {
            Node node;
            node["out_dir"] = rhs.out_dir;
            node["encoder"] = rhs.encoder;
            node["container"] = rhs.container;
            node["bitrate"] = rhs.bitrate;
            node["iframe_interval"] = rhs.iframe_interval;
            return node;
        }

        static bool decode(const Node& node, RecordSinkCompConfig& rhs)
        {
            if (!node.IsMap())
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "expect RecordSinkCompConfig node type is map:{}, but get {}", 
                    int(NodeType::Map), int(node.Type()));
                return false;
            }

            rhs.out_dir = node["out_dir"].as<std::string>();
            rhs.encoder = node["encoder"].as<uint32_t>();
            rhs.container = node["container"].as<uint32_t>();
            rhs.bitrate = node["bitrate"].as<uint32_t>();
            rhs.iframe_interval = node["iframe_interval"].as<uint32_t>();
            return true;
        }
    };

    template <>
    struct convert<DslPipelineServer::RtmpSinkCompConfig>
    {
        using RtmpSinkCompConfig = DslPipelineServer::RtmpSinkCompConfig;

        static Node encode(const RtmpSinkCompConfig& rhs)
        {
            Node node;
            node["uri"] = rhs.uri;
            node["bitrate"] = rhs.bitrate;
            node["iframe_interval"] = rhs.iframe_interval;
            return node;
        }

        static bool decode(const Node& node, RtmpSinkCompConfig& rhs)
        {
            if (!node.IsMap())
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "expect RtmpSinkCompConfig node type is map:{}, but get {}", 
                    int(NodeType::Map), int(node.Type()));
                return false;
            }

            rhs.uri = node["uri"].as<std::string>();
            rhs.bitrate = node["bitrate"].as<uint32_t>();
            rhs.iframe_interval = node["iframe_interval"].as<uint32_t>();
            return true;
        }
    };

    template <>
    struct convert<DslPipelineServer::RtspClientSinkCompConfig>
    {
        using RtspClientSinkCompConfig = DslPipelineServer::RtspClientSinkCompConfig;

        static Node encode(const RtspClientSinkCompConfig& rhs)
        {
            Node node;
            node["file_path"] = rhs.file_path;
            node["repeat_enabled"] = rhs.repeat_enabled;
            return node;
        }

        static bool decode(const Node& node, RtspClientSinkCompConfig& rhs)
        {
            if (!node.IsMap())
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "expect RtspClientSinkCompConfig node type is map:{}, but get {}", 
                    int(NodeType::Map), int(node.Type()));
                return false;
            }

            rhs.file_path = node["file_path"].as<std::string>();
            rhs.repeat_enabled = node["repeat_enabled"].as<bool>();
            return true;
        }
    };

    template <>
    struct convert<DslPipelineServer::RtspServerSinkCompConfig>
    {
        using RtspServerSinkCompConfig = DslPipelineServer::RtspServerSinkCompConfig;

        static Node encode(const RtspServerSinkCompConfig& rhs)
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

        static bool decode(const Node& node, RtspServerSinkCompConfig& rhs)
        {
            if (!node.IsMap())
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "expect RtspServerSinkCompConfig node type is map:{}, but get {}", 
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
    struct convert<DslPipelineServer::SinkCompConfig>
    {
        using SinkCompConfig = DslPipelineServer::SinkCompConfig;
        using AppSinkCompConfig = DslPipelineServer::AppSinkCompConfig;
        using V4l2SinkCompConfig = DslPipelineServer::V4l2SinkCompConfig;
        using FileSinkCompConfig = DslPipelineServer::FileSinkCompConfig;
        using RecordSinkCompConfig = DslPipelineServer::RecordSinkCompConfig;
        using RtmpSinkCompConfig = DslPipelineServer::RtmpSinkCompConfig;
        using RtspClientSinkCompConfig = DslPipelineServer::RtspClientSinkCompConfig;
        using RtspServerSinkCompConfig = DslPipelineServer::RtspServerSinkCompConfig;

        static Node encode(const SinkCompConfig& rhs)
        {
            Node node;
            node["type"] = rhs.type;
            switch (rhs.type)
            {
                case DslPipelineServer::APP_SINK_COMP_TYPE:
                {
                    node["config"] = rhs.app_config;
                    break;
                }
                case DslPipelineServer::V4L2_SINK_COMP_TYPE:
                {
                    node["config"] = rhs.v4l2_config;
                    break;
                }
                case DslPipelineServer::FILE_SINK_COMP_TYPE:
                {
                    node["config"] = rhs.file_config;
                    break;
                }
                case DslPipelineServer::RECORD_SINK_COMP_TYPE:
                {
                    node["config"] = rhs.record_config;
                    break;
                }
                case DslPipelineServer::RTMP_SINK_COMP_TYPE:
                {
                    node["config"] = rhs.rtmp_config;
                    break;
                }
                case DslPipelineServer::RTSP_CLIENT_SINK_COMP_TYPE:
                {
                    node["config"] = rhs.rtsp_client_config;
                    break;
                }
                case DslPipelineServer::RTSP_SERVER_SINK_COMP_TYPE:
                {
                    node["config"] = rhs.rtsp_server_config;
                    break;
                }
                default:
                {
                    PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "invalid sink component type: {}", int(rhs.type));
                    break;
                }
            }
            return node;
        }

        static bool decode(const Node& node, SinkCompConfig& rhs)
        {
            if (!node.IsMap())
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "expect SinkCompConfig node type is map:{}, but get {}", 
                    int(NodeType::Map), int(node.Type()));
                return false;
            }
            auto type_str = node["type"].as<std::string>();
            if (gStrToSinkCompType.end() == gStrToSinkCompType.find(type_str))
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "invalid sink component type {}, please check", type_str);
                return false;
            }
            auto type = gStrToSinkCompType[type_str];
            rhs.type = type;
            switch (rhs.type)
            {
                case DslPipelineServer::APP_SINK_COMP_TYPE:
                {
                    rhs.app_config = node["config"].as<AppSinkCompConfig>();
                    break;
                }
                case DslPipelineServer::V4L2_SINK_COMP_TYPE:
                {
                    rhs.csi_config = node["config"].as<V4l2SinkCompConfig>();
                    break;
                }
                case DslPipelineServer::FILE_SINK_COMP_TYPE:
                {
                    rhs.v4l2_config = node["config"].as<FileSinkCompConfig>();
                    break;
                }
                case DslPipelineServer::RECORD_SINK_COMP_TYPE:
                {
                    rhs.uri_config = node["config"].as<RecordSinkCompConfig>();
                    break;
                }
                case DslPipelineServer::RTMP_SINK_COMP_TYPE:
                {
                    rhs.file_config = node["config"].as<RtmpSinkCompConfig>();
                    break;
                }
                case DslPipelineServer::RTSP_CLIENT_SINK_COMP_TYPE:
                {
                    rhs.rtsp_config = node["config"].as<RtspClientSinkCompConfig>();
                    break;
                }
                case DslPipelineServer::RTSP_SERVER_SINK_COMP_TYPE:
                {
                    rhs.rtsp_config = node["config"].as<RtspServerSinkCompConfig>();
                    break;
                }
                default:
                {
                    PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "invalid sink component type: {}", int(rhs.type));
                    return false;
                }
            }
            return true;
        }
    };

} // namespace YAML

namespace DslPipelineServer
{

    // string to sink component type map
    std::map<std::string, SinkCompType> gStrToSinkCompType = {
        {"APP",                                 APP_SINK_COMP_TYPE},
        {"V4L2",                                V4L2_SINK_COMP_TYPE},
        {"FILE",                                FILE_SINK_COMP_TYPE},
        {"RECORD",                              RECORD_SINK_COMP_TYPE},
        {"RTMP",                                RTMP_SINK_COMP_TYPE},
        {"RTSP_CLIENT",                         RTSP_CLIENT_SINK_COMP_TYPE},
        {"RTSP_SERVER",                         RTSP_SERVER_SINK_COMP_TYPE},
    };

    // sink component type to string map
    std::map<SinkCompType, std::string> gSinkCompTypeToStr = {
        {APP_SINK_COMP_TYPE,                    "APP"},
        {V4L2_SINK_COMP_TYPE,                   "V4L2"},
        {FILE_SINK_COMP_TYPE,                   "FILE"},
        {RECORD_SINK_COMP_TYPE,                 "RECORD"},
        {RTMP_SINK_COMP_TYPE,                   "RTMP"},
        {RTSP_CLIENT_SINK_COMP_TYPE,            "RTSP_CLIENT"},
        {RTSP_SERVER_SINK_COMP_TYPE,            "RTSP_SERVER"},
    };

    void logValidSinkCompType()
    {
        PIPELINE_LOG(PIPELINE_LOG_LEVEL_INFO, "valid sink component type as follows:");
        for (auto it = gSinkCompTypeToStr.begin(); it != gSinkCompTypeToStr.end(); it++)
        {
            auto type = it->first;
            auto type_str = it->second;
            PIPELINE_LOG(PIPELINE_LOG_LEVEL_INFO, "{} ----> {}", type, type_str);
        }
        return;
    }

    int convertStrToSinkCompType(const std::string type_str, SinkCompType& type)
    {
        if (gStrToSinkCompType.end() == gStrToSinkCompType.find(type_str))
            return -1;

        type = gStrToSinkCompType[type_str];
        return 0;
    }

    int convertSinkCompTypeToStr(const SinkCompType type, std::string& type_str)
    {
        if (gSinkCompTypeToStr.end() == gSinkCompTypeToStr.find(type))
            return -1;

        type_str = gSinkCompTypeToStr[type];
        return 0;
    }

    int parseSinkCompConfigFromNode(const YAML::Node& node, SinkCompConfig& config)
    {
        try
        {
            config = node["config"].as<SinkCompConfig>();
        }
        catch (const std::exception &e)
        {
            PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "parse sink component node error:\n {}", e.what());
            return -1;
        }
        return 0;
    }

    int dumpSinkCompConfigToNode(const SinkCompConfig& config, YAML::Node& node)
    {
        try
        {
            node["config"] = config;
        }
        catch (const std::exception &e)
        {
            PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "dump sink component config error:\n {}", e.what());
            return -1;
        }
        return 0;
    }

} // namespace DslPipelineServer