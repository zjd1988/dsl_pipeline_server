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
#include "common/logger.h"
#include "common/pipeline_config.h"
#include "pipeline/pipeline_manager.h"

namespace DslPipelineServer
{

    static std::string generateUniqueString()
    {
        auto now = std::chrono::high_resolution_clock::now();
        auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
        auto value = now_ms.time_since_epoch();
        std::hash<decltype(value)> hash_fn;
        std::stringstream ss;
        ss << hash_fn(value);
        return ss.str();
    }

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
            name = "pipeline_" + generateUniqueString();
            config.name = name;
        }
        if (m_pipelines.end() != m_pipelines.find(name))
        {
            PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "pipeline: {} already exists", name);
            return -1;
        }
        std::shared_ptr<DslPipeline> pipeline(new DslPipeline(config))
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
        if (m_pipelines.end() != it)
        {
            m_pipelines[name].reset();
            m_pipelines.erase(it);
        }
        return 0;
    }

    void PipelineManager::stopPipelines(const std::vector<std::string> names)
    {
        if (0 == names.size())
        {
            for (auto it = m_pipelines.begin(); it != m_pipelines.end(); it++)
            {
                std::string name = it->first;
                if (0 != stopPipeline(name))
                {
                    PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "stop pipeline: {} fail", name);
                }
                else
                {
                    PIPELINE_LOG(PIPELINE_LOG_LEVEL_INFO, "stop pipeline: {} success", name);
                }
            }
        }
        else
        {
            for (size_t index = 0; index < names.size(); index++)
            {
                std::string name = names[index];
                if (0 != stopPipeline(name))
                {
                    PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "stop pipeline: {} fail", name);
                }
                else
                {
                    PIPELINE_LOG(PIPELINE_LOG_LEVEL_INFO, "stop pipeline: {} success", name);
                }
            }
        }
        return;
    }

} // namespace DslPipelineServer
