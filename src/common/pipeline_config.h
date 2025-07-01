/********************************************
// Filename: pipeline_config.h
// Created by zhaojiadi on 2023/4/29
// Description:

********************************************/
#pragma once
#include <map>
#include <vector>
#include <string>
#include <memory>
#include "common/logger.h"
#include "component/base_config.h"
#include "component/source_config.h"
#include "component/sink_config.h"
#include "component/infer_config.h"
#include "component/tracker_config.h"
#include "component/osd_config.h"

namespace DslPipelineServer
{

    typedef struct PipelineConfig
    {
        std::string                                            name;
        std::vector<std::shared_ptr<BaseCompConfig>>           component_configs;
    } PipelineConfig;

    int parsePipelineConfigFromStr(const std::string& config_str, PipelineConfig& config);
    int parsePipelineConfigFromFile(const std::string& config_file, PipelineConfig& config);

} // namespace DslPipelineServer