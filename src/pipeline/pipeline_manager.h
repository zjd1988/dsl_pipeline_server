/********************************************
// Filename: pipeline_manager.h
// Created by zhaojiadi on 2022/10/17
// Description:

********************************************/
#pragma once
#include <map>
#include <mutex>
#include <string>
#include <memory>
#include "common/non_copyable.h"
#include "common/pipeline_config.h"
#include "pipeline/dsl_pipeline.h"

namespace DslPipelineServer
{

    class PipelineManager : public NonCopyable
    {
    public:
        PipelineManager() = default;
        ~PipelineManager();
        int createPipelineFromConfig(const PipelineConfig& config);
        int createPipelineFromConfigFile(const std::string config_file);
        int createPipelineFromConfigStr(const std::string config_str);
        int stopPipeline(const std::string name);
        void stopPipelines(const std::vector<std::string> names = {});

    private:
        std::map<std::string, std::shared_ptr<DslPipeline>>        m_pipelines;
        std::mutex                                                 m_mutex;
    };

} // namespace DslPipelineServer