/********************************************
// Filename: tracker_config.cpp
// Created by zhaojiadi on 2023/4/29
// Description:

********************************************/
#include <fstream>
#include <sstream>
#include "common/logger.h"
#include "component/tracker_config.h"

namespace YAML
{

    template <>
    struct convert<DslPipelineServer::TrackerCompConfig>
    {
        using TrackerCompConfig = DslPipelineServer::TrackerCompConfig;

        static Node encode(const TrackerCompConfig& rhs)
        {
            Node node;
            node["config_file"] = rhs.config_file;
            node["width"] = rhs.width;
            node["height"] = rhs.height;
            return node;
        }

        static bool decode(const Node& node, TrackerCompConfig& rhs)
        {
            if (!node.IsMap())
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "expect TrackerCompConfig node type is map:{}, but get {}", 
                    int(NodeType::Map), int(node.Type()));
                return false;
            }

            rhs.config_file = node["config_file"].as<std::string>();
            rhs.width = node["width"].as<uint32_t>();
            rhs.height = node["height"].as<uint32_t>();
            return true;
        }
    };

} // namespace YAML

namespace DslPipelineServer
{

    void parseTrackerCompConfigFromNode(const YAML::Node& node, TrackerCompConfig& config)
    {
        config = node.as<TrackerCompConfig>();
        return;
    }

    void dumpTrackerCompConfigToNode(const TrackerCompConfig& config, YAML::Node& node)
    {

        node = config;
        return;
    }

} // namespace DslPipelineServer