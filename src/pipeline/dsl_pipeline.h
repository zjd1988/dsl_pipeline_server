/********************************************
// Filename: dsl_pipeline.h
// Created by zhaojiadi on 2022/10/17
// Description:

********************************************/
#pragma once
#include <thread>
#include "eventqueue.h"
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
        std::string getPipelineName() { return m_name; }
        void sendEosEventToLoop();

    private:
        typedef enum DslPipelineEvent
        {
            EVENT_NONE = 0,
            EVENT_EOS,
            EVENT_STOP,
            EVENT_PAUSE,
        } DslPipelineEvent;

    private:
        void eventLoop();
        void noneEventProcess();
        void stopEventProcess();
        void eosEventProcess();
        int createComponents(const PipelineConfig& config, std::vector<std::string>& comp_names);
        int dslSourceComponentCreate(const std::string name, const SourceCompConfig& config);
        int dslInferComponentCreate(const std::string name, const InferCompConfig& config);
        int dslTrackerComponentCreate(const std::string name, const TrackerCompConfig& config);
        int dslOsdComponentCreate(const std::string name, const OsdCompConfig& config);
        int dslSinkComponentCreate(const std::string name, const SinkCompConfig& config);

    private:
        eventpp::EventQueue<int, void()>        m_event_queue;
        std::unique_ptr<std::thread>            m_even_loop_thread;
        std::unique_ptr<DslThread>              m_dsl_thread;
        std::string                             m_name;
        bool                                    m_init_flag = false;
        std::atomic<bool>                       m_event_loop_exit;
    };

} // namespace DslPipelineServer