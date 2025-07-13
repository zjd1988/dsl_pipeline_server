/********************************************
// Filename: dsl_common.h
// Created by zhaojiadi on 2023/4/29
// Description:

********************************************/
#pragma once
#include <glib.h>
#include "DslApi.h"
#include <functional>
#include <iostream>
#include "common/non_copyable.h"

namespace DslPipelineServer
{

    typedef struct DslThreadMetaData
    {
        std::wstring pipeline;
        std::vector<std::wstring> components;
    } DslThreadMetaData;

    class DslThread : public NonCopyable
    {
    public:
        DslThread(const std::string pipeline, const std::vector<std::string>& components);
        bool startPipeline();
        void stopPipeline();
        bool isRunning();
        ~DslThread();

    private:
        DslReturnType deletePipeline(DslThreadMetaData& metadata);

    private:
        static gpointer threadFunc(gpointer data)
        {
            DslThread* dsl_thread = static_cast<DslThread*>(data);

            auto& metadata = dsl_thread->m_thread_meta;
            // Play the pipeline
            DslReturnType retval = dsl_pipeline_play(metadata.pipeline.c_str());
            if (retval != DSL_RESULT_SUCCESS)
                return nullptr;

            // blocking call
            dsl_pipeline_main_loop_run(metadata.pipeline.c_str());
            dsl_thread->deletePipeline(metadata);
            return nullptr;
        }
        

    private:
        GThread*                            m_thread_id;
        std::string                         m_thread_name;
        std::vector<std::wstring>           m_components;
        DslThreadMetaData                   m_thread_meta;
    };

} // namespace DslPipelineServer