/********************************************
// Filename: pipeline_server.h
// Created by zhaojiadi on 2022/10/17
// Description:

********************************************/
#pragma once
#include <memory>
#include <glib.h>
#include "HttpServer.h"
#include "hlog.h"
#include "common/non_copyable.h"
#include "pipeline/pipeline_manager.h"

namespace DslPipelineServer
{

    class PipelineServer : public NonCopyable
    {
    public:
        PipelineServer(const PipelineServerConfig server_config);
        ~PipelineServer();
        int startServer();
        int stopServer();

    private:
        int createPipeline(HttpRequest* req, HttpResponse* resp);
        int stopPipeline(HttpRequest* req, HttpResponse* resp);

    private:
        hv::HttpService                           m_router;
        hv::HttpServer                            m_server;
        std::unique_ptr<PipelineManager>          m_pipeline_manager;
    };

} // namespace DslPipelineServer