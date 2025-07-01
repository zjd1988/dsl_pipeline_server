/********************************************
// Filename: pipeline_server.cpp
// Created by zhaojiadi on 2022/10/17
// Description:

********************************************/
#include <thread>
#include "server/pipeline_server.h"
#include "pipeline/pipeline_manager.h"

namespace DslPipelineServer
{

    PipelineServer::PipelineServer(const PipelineServerConfig server_config)
    {
        std::string ip_addr = server_config.ip_addr;
        int port_num = server_config.port_num;
        int thread_num = (0 >= server_config.thread_num) ? std::thread::hardware_concurrency() : server_config.thread_num;
        // disbale hv log
        hlog_disable();
        // register server apis
        m_router.POST("/create_pipeline", std::bind(&PipelineServer::createPipeline, this, std::placeholders::_1, std::placeholders::_2));
        m_router.POST("/stop_pipeline", std::bind(&PipelineServer::stopPipeline, this, std::placeholders::_1, std::placeholders::_2));

        // register http service, and set server config
        m_server.registerHttpService(&m_router);
        m_server.setHost(ip_addr.c_str());
        m_server.setPort(port_num);
        m_server.setThreadNum(thread_num);

        // init pipeline manager
        m_pipeline_manager.reset(new PipelineManager());
    }

    PipelineServer::~PipelineServer()
    {
        if (nullptr != m_pipeline_manager.get())
        {
            m_pipeline_manager.reset();
        }
        stopServer();
    }

    int PipelineServer::startServer()
    {
        return m_server.start();
    }

    int PipelineServer::stopServer()
    {
        return m_server.stop();
    }

    int PipelineServer::createPipeline(HttpRequest* req, HttpResponse* resp)
    {
        const std::string& req_body = req->Body();
        std::string result;
        // if (nullptr != m_pipeline_manager.get() && 0 != m_pipeline_manager->createPipeline())
        // {

        // }
        return resp->Data((void*)result.c_str(), result.size(), false);
    }

    int PipelineServer::stopPipeline(HttpRequest* req, HttpResponse* resp)
    {
        const std::string& req_body = req->Body();
        std::string result;
        return resp->Data((void*)result.c_str(), result.size(), false);
    }

} // namespace DslPipelineServer