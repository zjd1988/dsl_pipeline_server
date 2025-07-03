/********************************************
// Filename: server_main.cpp
// Created by zhaojiadi on 2022/10/17
// Description:

********************************************/
#include <iostream>
#include "cxxopts.hpp"
#include "ghc/filesystem.h"
#include "common/logger.h"
#include "pipeline/pipeline_manager.h"
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
    std::string config_file;

    cxxopts::Options arg_options("./dsl_pipeline_server", "dsl pipeline server");
    arg_options.add_options()
        ("log_path", "dsl pipeline test log path", cxxopts::value<std::string>()->default_value(""))
        ("log_level", "dsl pipeline test log level, for example: TRACE = 0, DEBUG = 1 INFO = 2, WARN = 3, ERROR = 4, FATAL = 5",
            cxxopts::value<int>()->default_value("2"))
        ("config_file", "dsl pipeline test config file")
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
    config_file = parse_result["config_file"].as<std::string>();

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

    // 4 init pipeline manager
    std::unique_ptr<DslPipelineServer::PipelineManager> pipeline_manager(new DslPipelineServer::PipelineManager());
    if (nullptr == pipeline_manager.get())
    {
        PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "init pipeline manager fail");
        goto FINAL;
    }

    // start pipeline with config file
    if (0 != pipeline_manager->createPipelineFromConfigFile(config_file))
    {
        PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "start pipeline form config file {} fail");
        goto FINAL;
    }

    // 6 check app run flag
    while (gAppRunFlag)
    {
        sleep(1);
    }

    // 7 final process, release server and logger
FINAL:
    if (nullptr != pipeline_manager.get())
    {
        pipeline_manager.reset();
    }

    DslPipelineServer::PipelineLogger::Instance().stopPipelineLogger();
    return 0;
}