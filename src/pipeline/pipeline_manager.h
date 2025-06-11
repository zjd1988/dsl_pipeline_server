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
        static PipelineManager& Instance();
        int createPipeline(const PipelineConfig& pipeline_config);
        int createPipeline(const std::string config_file);
        int stopPipeline(const std::string pipeline_name);
        void stopPipelines();

    private:
        PipelineManager() = default;
        ~PipelineManager();

    private:
        std::map<std::string, std::shared_ptr<DslPipeline>>        m_pipelines;
        std::mutex                                                 m_mutex;
    };

} // namespace DslPipelineServer