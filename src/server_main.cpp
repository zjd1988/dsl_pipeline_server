/********************************************
// Filename: server_main.cpp
// Created by zhaojiadi on 2022/10/17
// Description:

********************************************/
#include <iostream>
#include "cxxopts/cxxopts.hpp"
#include "ghc/filesystem.h"
#include "common/logger.h"
#include "common/server_config.h"
#include "server/pipeline_server.h"
namespace fs = ghc::filesystem;

bool gAppRunFlag = true;
void sigHandle(int signo)
{
    PIPELINE_LOG(PIPELINE_LOG_LEVEL_INFO, "receive signal: {}", signo);
    gAppRunFlag = false;
    return;
}

int main(int argc, char* argv[])
{
    // 1 parse arg
    std::string log_path;
    int log_level;
    std::string server_ip_addr;
    int server_port_num;
    int server_thread_num;
    cxxopts::Options arg_options("./dsl_pipeline_server", "dsl pipeline server");
    arg_options.add_options()
        ("log_path", "dsl pipeline server log path", cxxopts::value<std::string>()->default_value(""))
        ("log_level", "dsl pipeline server log level, for example: TRACE = 0, DEBUG = 1 INFO = 2, WARN = 3, ERROR = 4, FATAL = 5",
            cxxopts::value<int>()->default_value("2"))
        ("ip_addr", "dsl pipeline server listen ip, default is 0.0.0.0", cxxopts::value<std::string>()->default_value("0.0.0.0"))
        ("port_num", "dsl pipeline server bind port, default is 12345", cxxopts::value<int>()->default_value(12345))
        ("thread_num", "dsl pipeline server thread num, default is 1", cxxopts::value<int>()->default_value(1))
        // help
        ("help", "print usage");
    arg_options.allow_unrecognised_options();
    auto parse_result = arg_options.parse(argc, argv);
    if (parse_result.count("help"))
    {
        std::cerr << arg_options.help() << std::endl;
        return -1;
    }

    log_path = parse_result["log_path"].as<std::string>();
    log_level = parse_result["log_level"].as<int>();
    server_ip_addr = parse_result["ip_addr"].as<std::string>();
    server_port_num = parse_result["port_num"].as<int>();
    server_thread_num = parse_result["thread_num"].as<int>();

    // 2 init log
    if ("" != log_path)
    {
        fs::path fs_log_path{log_path};
        fs::path fs_log_full_path = fs::absolute(fs_log_path);
        log_path = fs_log_full_path.string();
    }
    DslPipelineServer::PipelineLogger::Instance().initPipelineLogger(log_path, log_level);
    PIPELINE_LOG(PIPELINE_LOG_LEVEL_INFO, "pipeline logger init done, {} {}", log_path, log_level);

    // 3 register signale handle
    signal(SIGINT, sigHandle);
    signal(SIGTERM, sigHandle);

    // 4 init pipeline server
    DslPipelineServer::PipelineServerConfig config;
    config.ip_addr = server_ip_addr;
    config.port_num = server_port_num;
    config.thread_num = server_thread_num;
    std::unique_ptr<DslPipelineServer::PipelineServer> pipeline_server(new DslPipelineServer::PipelineServer(config));
    if (null_ptr == pipeline_server.get())
    {
        PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "init pipeline server fail");
        goto FINAL;
    }
    if (0 != pipeline_server->startServer())
    {
        PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "start pipeline server fail");
        goto FINAL;
    }

    // 5 check app run flag
    while (gAppRunFlag)
    {
        sleep(1);
    }

    // 6 final process, release server and logger
FINAL:
    if (nullptr != pipeline_server.get())
    {
        pipeline_server.reset();
    }

    DslPipelineServer::PipelineLogger::Instance().stopPipelineLogger();
    return 0;
}