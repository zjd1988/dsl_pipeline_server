/********************************************
// Filename: tracker_config.h
// Created by zhaojiadi on 2023/4/29
// Description:

********************************************/
#pragma once
#include <map>
#include <vector>
#include <string>
#include <yaml-cpp/yaml.h>
#include "component/base_config.h"

namespace DslPipelineServer
{

    typedef struct TrackerCompConfig : public BaseCompConfig
    {
        std::string                                    config_file;    // relative or absolute pathspec to a valid config text file. Set to NULL or empty string to omit.
        uint32_t                                       width;          // Frame width at which the tracker is to operate, in pixels.
        uint32_t                                       height;         // Frame height at which the tracker is to operate, in pixels.
    } TrackerCompConfig;

    void parseTrackerCompConfigFromNode(const YAML::Node& node, TrackerCompConfig& config);
    void dumpTrackerCompConfigToNode(const TrackerCompConfig& config, YAML::Node& node);

} // namespace DslPipelineServer