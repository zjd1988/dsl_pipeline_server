/********************************************
// Filename: server_config.h
// Created by zhaojiadi on 2023/4/29
// Description:

********************************************/
#pragma once
#include <string>

namespace DslPipelineServer
{

    typedef struct PipelineServerConfig
    {
        std::string                  ip_addr;
        int                          port_num;
        int                          thread_num;
    } PipelineServerConfig;

    typedef struct ServerResp
    {
        int                          error_code;
        std::string                  error_str;
    } ServerResp;

} // namespace DslPipelineServer