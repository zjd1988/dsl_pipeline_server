/********************************************
// Filename: dsl_pipeline.h
// Created by zhaojiadi on 2022/10/17
// Description:

********************************************/
#pragma once
#include "common/non_copyable.h"

namespace DslPipelineServer
{

    class DslPipeline : public NonCopyable
    {
    public:
        DslPipeline(const PipelineConfig& pipeline_config);
        DslPipeline(const std::string config_file);
        ~DslPipeline();

    private:
        dslSourceCreate(std::string );
    };

} // namespace DslPipelineServer