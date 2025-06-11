/********************************************
// Filename: pipeline_manager.cpp
// Created by zhaojiadi on 2022/10/17
// Description:

********************************************/
#include "common/logger.h"
#include "pipeline/pipeline_manager.h"

namespace DslPipelineServer
{

    PipelineManager& PipelineManager::Instance()
    {
        static PipelineManager manager;
        return manager;
    }

    PipelineManager::~PipelineManager()
    {
        stopPipelines();
    }

    int PipelineManager::createPipeline(const PipelineConfig& pipeline_config)
    {
        return 0;
    }

    int PipelineManager::createPipeline(const std::string config_file)
    {
        return 0;
    }

    int PipelineManager::stopPipeline(const std::string pipeline_name)
    {
        return 0;
    }

    void PipelineManager::stopPipelines()
    {
        for (auto it = m_pipelines.begin(); it != m_pipelines.end(); it++)
        {
            std::string pipeline_name = it->first;
            if (0 != stopPipeline(pipeline_name))
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "stop pipeline: {} fail", pipeline_name);
            }
            else
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_INFO, "stop pipeline: {} success", pipeline_name);
            }
        }
        return;
    }

} // namespace DslPipelineServer
