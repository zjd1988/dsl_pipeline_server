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
#include "component/base_config.h"

namespace DslPipelineServer
{

    typedef struct OsdCompConfig : public BaseCompConfig
    {
        bool                                           text_enable;     // set to true to enable object text display, false otherwise.
        bool                                           clock_enable;    // set to true to enable clock display, false otherwise.
        bool                                           bbox_enable;     // set to true to enable bounding box display, false otherwise.
        bool                                           mask_enable;     // set to true to enable segmentation mask display, false otherwise.
    } OsdCompConfig;

    void parseOsdCompConfigFromNode(const YAML::Node& node, OsdCompConfig& config);
    void dumpOsdCompConfigToNode(const OsdCompConfig& config, YAML::Node& node);

} // namespace DslPipelineServer