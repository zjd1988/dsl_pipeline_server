/********************************************
// Filename: dsl_pipeline.h
// Created by zhaojiadi on 2022/10/17
// Description:

********************************************/
#pragma once
#include "common/non_copyable.h"
#include "common/dsl_thread.h"
#include "common/pipeline_config.h"

namespace DslPipelineServer
{

    class DslPipeline : public NonCopyable
    {
    public:
        DslPipeline(const PipelineConfig& config, const std::string name = "");
        ~DslPipeline();
        bool getInitFlag() { return m_init_flag; }

    private:
        int createComponents(const PipelineConfig& config);
        int dslSourceComponentCreate(const std::string name, const SourceCompConfig& config);
        int dslInferComponentCreate(const std::string name, const InferCompConfig& config);
        int dslTrackerComponentCreate(const std::string name, const TrackerCompConfig& config);
        int dslOsdComponentCreate(const std::string name, const OsdCompConfig& config);
        int dslSinkComponentCreate(const std::string name, const SinkCompConfig& config);

    private:
        std::unique_ptr<DslThread>              m_thread;
        std::string                             m_name;
        bool                                    m_init_flag = false;
    };

} // namespace DslPipelineServer