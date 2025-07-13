/********************************************
// Filename: dsl_thread.cpp
// Created by zhaojiadi on 2023/4/29
// Description:

********************************************/
#include "common/logger.h"
#include "common/dsl_common.h"
#include "common/dsl_thread.h"

namespace DslPipelineServer
{

    DslThread::DslThread(const std::string pipeline, const std::vector<std::string>& components)
    {
        m_thread_id = nullptr;
        m_thread_name = pipeline;
        for (size_t index = 0; index < components.size(); index++)
        {
            m_components.push_back(convertStrToWStr(components[index]));
        }
        m_thread_meta.components = m_components;
        m_thread_meta.pipeline = convertStrToWStr(pipeline);
        return;
    }

    bool DslThread::startPipeline()
    {
        if (m_thread_id)
        {
            PIPELINE_LOG(PIPELINE_LOG_LEVEL_WARN, "pipeline {} thread already started!", m_thread_name);
            return false;
        }

        m_thread_id = g_thread_new(m_thread_name.c_str(), threadFunc, this);
        if (!m_thread_id)
        {
            PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "failed to create pipeline {} thread!", m_thread_name);
            return false;
        }
        return true;
    }

    void DslThread::stopPipeline()
    {
        if (!m_thread_id)
        {
            PIPELINE_LOG(PIPELINE_LOG_LEVEL_WARN, "{} thread not started or already joined!", m_thread_name);
            return;
        }
        dsl_pipeline_stop(m_thread_meta.pipeline.c_str());
        dsl_pipeline_main_loop_quit(m_thread_meta.pipeline.c_str());
        g_thread_join(m_thread_id);
        m_thread_id = nullptr;
        return;
    }

    bool DslThread::isRunning()
    {
        return m_thread_id != nullptr;
    }

    DslThread::~DslThread()
    {
        if (m_thread_id)
        {
            PIPELINE_LOG(PIPELINE_LOG_LEVEL_INFO, "Thread not joined, calling stopPipeline in destructor.");
            stopPipeline();
        }
    }

    DslReturnType DslThread::deletePipeline(DslThreadMetaData& metadata)
    {
        PIPELINE_LOG(PIPELINE_LOG_LEVEL_INFO, "stoping and deleting Pipeline {}", m_thread_name);

        // Stop the pipeline
        DslReturnType retval = dsl_pipeline_stop(metadata.pipeline.c_str());
        if (retval != DSL_RESULT_SUCCESS)
            return retval;

        // Delete the Pipeline first, then the components. 
        retval = dsl_pipeline_delete(metadata.pipeline.c_str());
        if (retval != DSL_RESULT_SUCCESS)
            return retval;

        // Now safe to delete all components for this Pipeline
        std::vector<const wchar_t*> component_names;
        for (size_t index = 0; index < metadata.components.size(); index++)
        {
            component_names.push_back(metadata.components[index].c_str());
        }
        component_names.push_back(nullptr);
        retval = dsl_component_delete_many(&component_names[0]);
        if (retval != DSL_RESULT_SUCCESS)
            return retval;

        PIPELINE_LOG(PIPELINE_LOG_LEVEL_INFO, "Pipeline {} deleted successfully", m_thread_name);
        return retval;
    }

} // namespace DslPipelineServer