/********************************************
// Filename: osd_config.cpp
// Created by zhaojiadi on 2023/4/29
// Description:

********************************************/
#include <fstream>
#include <sstream>
#include "common/logger.h"
#include "component/osd_config.h"

namespace YAML
{

    template <>
    struct convert<DslPipelineServer::OsdCompConfig>
    {
        using OsdCompConfig = DslPipelineServer::OsdCompConfig;

        static Node encode(const OsdCompConfig& rhs)
        {
            Node node;
            node["text_enable"] = rhs.text_enable;
            node["clock_enable"] = rhs.clock_enable;
            node["bbox_enable"] = rhs.bbox_enable;
            node["mask_enable"] = rhs.mask_enable;
            return node;
        }

        static bool decode(const Node& node, OsdCompConfig& rhs)
        {
            if (!node.IsMap())
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "expect OsdCompConfig node type is map:{}, but get {}", 
                    int(NodeType::Map), int(node.Type()));
                return false;
            }

            rhs.text_enable = node["text_enable"].as<bool>();
            rhs.clock_enable = node["clock_enable"].as<bool>();
            rhs.bbox_enable = node["bbox_enable"].as<bool>();
            rhs.mask_enable = node["mask_enable"].as<bool>();
            return true;
        }
    };

} // namespace YAML

namespace DslPipelineServer
{

    void parseOsdCompConfigFromNode(const YAML::Node& node, OsdCompConfig& config)
    {
        config = node.as<OsdCompConfig>();
        return;
    }

    void dumpOsdCompConfigToNode(const OsdCompConfig& config, YAML::Node& node)
    {
        node = config;
        return;
    }

} // namespace DslPipelineServer