/********************************************
// Filename: pipeline_manager.cpp
// Created by zhaojiadi on 2022/10/17
// Description:

********************************************/
#include <iostream>
#include <string>
#include <chrono>
#include <functional>
#include <sstream>
#include <glib.h>
#include "DslApi.h"
#include "common/logger.h"
#include "common/uuid.h"
#include "common/pipeline_config.h"
#include "pipeline/pipeline_manager.h"

namespace DslPipelineServer
{

    PipelineManager::~PipelineManager()
    {
        stopPipelines();
        dsl_delete_all();
    }

    int PipelineManager::createPipelineFromConfig(const PipelineConfig& config)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        std::string name = config.name;
        if ("" == name)
        {
            PIPELINE_LOG(PIPELINE_LOG_LEVEL_WARN, "pipeline name is null, will generate random name based on time and hash");
            name = "pipeline_" + genNewUUID();
        }
        if (m_pipelines.end() != m_pipelines.find(name))
        {
            PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "pipeline: {} already exists", name);
            return -1;
        }
        std::shared_ptr<DslPipeline> pipeline(new DslPipeline(config, name));
        if (nullptr == pipeline.get() || false == pipeline->getInitFlag())
        {
            PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "creat pipeline: {} fail", name);
            return -1;
        }
        PIPELINE_LOG(PIPELINE_LOG_LEVEL_INFO, "create pipeline: {} success", name);
        m_pipelines[name] = pipeline;
        return 0;
    }

    int PipelineManager::createPipelineFromConfigFile(const std::string config_file)
    {
        PipelineConfig config;
        if (0 != parsePipelineConfigFromFile(config_file, config))
        {
            PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "parse pipeline config file: {} fail", config_file);
            return -1;
        }
        return createPipelineFromConfig(config);
    }

    int PipelineManager::createPipelineFromConfigStr(const std::string config_str)
    {
        PipelineConfig config;
        if (0 != parsePipelineConfigFromStr(config_str, config))
        {
            PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "parse pipeline config str fail:\n{}", config_str);
            return -1;
        }
        return createPipelineFromConfig(config);
    }

    int PipelineManager::stopPipeline(const std::string name)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        auto it = m_pipelines.find(name);
        if (m_pipelines.end() != it && nullptr != it->second.get())
        {
            it->second.reset();
            m_pipelines.erase(it);
        }
        return 0;
    }

    void PipelineManager::stopPipelines(const std::vector<std::string> pipeline_names)
    {
        std::vector<std::string> stop_names = pipeline_names;
        if (0 == stop_names.size())
        {
            for (auto it = m_pipelines.begin(); it != m_pipelines.end(); it++)
            {
                std::string name = it->first;
                stop_names.emplace_back(name);
            }
        }

        for (size_t index = 0; index < stop_names.size(); index++)
        {
            std::string name = stop_names[index];
            if (0 != stopPipeline(name))
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "stop pipeline: {} fail", name);
            }
            else
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_INFO, "stop pipeline: {} success", name);
            }
        }
        return;
    }

} // namespace DslPipelineServer
