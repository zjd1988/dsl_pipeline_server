/********************************************
// Filename: server_main.cpp
// Created by zhaojiadi on 2022/10/17
// Description:

********************************************/
#include <iostream>
#include "cxxopts/cxxopts.hpp"
#include "ghc/filesystem.h"
#include "server/pipeline_server.h"
namespace fs = ghc::filesystem;


bool gAppRunFlag = false;
void sigHandle(int signo)
{
    TRACKER_LOG(TRACKER_LOG_LEVEL_INFO, "receive signal: {}", signo);
    gAppRunFlag = false;
    return;
}

int main(int argc, char* argv[])
{
    // 1 parse arg
    std::string config_path;
    std::string log_path;
    int log_level;
    cxxopts::Options arg_options("./dsl_pipeline_server", "dsl pipeline server");
    arg_options.add_options()
        ("log_path", "dsl pipeline server log path", cxxopts::value<std::string>()->default_value(""))
        ("log_level", "dsl pipeline server log level, for example: TRACE = 0, DEBUG = 1 INFO = 2, WARN = 3, ERROR = 4, FATAL = 5,",
            cxxopts::value<int>()->default_value("2"))
        ("config_path", "dsl pipeline server yaml config path", cxxopts::value<std::string>()->default_value(""))
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
    config_path = parse_result["config_path"].as<std::string>();

    // 2 init log
    fs::path fs_log_path{log_path};
    fs::path fs_log_full_path = fs::absolute(fs_log_path);
    log_path = fs_log_full_path.string();
    TrackerFramework::TrackerLog::Instance().initTrackerLog(log_path, log_level);
    TRACKER_LOG(TRACKER_LOG_LEVEL_INFO, "logger init done, {} {}", log_path, log_level);

    // 3 parse pipeline config from yaml file
    fs::path fs_config_path{config_path};
    fs::path fs_config_full_path = fs::absolute(fs_config_path);
    config_path = fs_config_full_path.string();

    return 0;
}