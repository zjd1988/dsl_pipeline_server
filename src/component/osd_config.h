/********************************************
// Filename: osd_config.h
// Created by zhaojiadi on 2023/4/29
// Description:

********************************************/
#pragma once
#include <map>
#include <vector>
#include <string>
#include <yaml-cpp/yaml.h>

namespace DslPipelineServer
{

    typedef struct OsdCompConfig
    {
        bool                                           text_enable;     // set to true to enable object text display, false otherwise.
        bool                                           clock_enable;    // set to true to enable clock display, false otherwise.
        bool                                           bbox_enable;     // set to true to enable bounding box display, false otherwise.
        bool                                           mask_enable;     // set to true to enable segmentation mask display, false otherwise.
    } OsdCompConfig;

    int parseOsdCompConfigFromNode(const YAML::Node& node, OsdCompConfig& config);
    int dumpOsdCompConfigToNode(const OsdCompConfig& config, YAML::Node& node);

} // namespace DslPipelineServer