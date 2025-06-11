/********************************************
// Filename: logger.cpp
// Created by zhaojiadi on 2023/4/29
// Description:

********************************************/
#include "common/logger.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"


#define LOG_FILE_SIZE 10 * 1024 * 1024
#define LOG_FILE_NUM 3

namespace DslPipelineServer 
{

    PipelineLogger::PipelineLogger()
    {
        // std::string logger_name = "GLDAI_ALGO";
        // std::string log_file_name = "./log.txt";
        // int log_level = PIPELINE_LOG_LEVEL_INFO;
        // initPipelineLogger(logger_name, log_file_name, log_level);
    }

    PipelineLogger& PipelineLogger::Instance()
    {
        static PipelineLogger log;
        return log;
    }

    void PipelineLogger::initPipelineLogger(std::string file_name, int log_level)
    {
        // set log level
        if (log_level != PIPELINE_LOG_LEVEL_TRACE && log_level != PIPELINE_LOG_LEVEL_DEBUG && 
            log_level != PIPELINE_LOG_LEVEL_INFO  && log_level != PIPELINE_LOG_LEVEL_WARN  && 
            log_level != PIPELINE_LOG_LEVEL_ERROR && log_level != PIPELINE_LOG_LEVEL_FATAL && 
            log_level != PIPELINE_LOG_LEVEL_OFF)
            log_level = PIPELINE_LOG_LEVEL_INFO;

        // set log rotate
        int log_file_size = LOG_FILE_SIZE;
        if (log_file_size <= 0)
            log_file_size = 10 * 1024 * 1024; // 10MB
        int num_log_files = LOG_FILE_NUM;
            num_log_files = 3;
        if (file_name.empty())
            file_name = "tracker_algo.log";
        std::string logger_name = "DSL_PIPELINE";

        std::cout << "log level: " << log_level << std::endl;
        std::cout << "logger name: " << logger_name << std::endl;
        std::cout << "log file path: " << file_name << std::endl;

        m_logger.reset();
        if ("" != file_name)
        {
            auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(file_name, log_file_size, num_log_files);
            m_logger = std::unique_ptr<spdlog::logger>(new spdlog::logger(logger_name, {console_sink, file_sink}));
        }
        else
        {
            auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            m_logger = std::unique_ptr<spdlog::logger>(new spdlog::logger(logger_name, {console_sink}));
        }

        spdlog::register_logger(m_logger);
        // set log pattern
        m_logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e %z] [%n] [%^---%L---%$] [thread %t] [%g:%# %!] %v");
        spdlog::set_default_logger(spdlog::get(logger_name));
        // spdlog::flush_on(spdlog::level::info);
        spdlog::flush_on(spdlog::level::debug);
        spdlog::set_level(static_cast<spdlog::level::level_enum>(log_level));
    }

    void PipelineLogger::stopPipelineLogger()
    {
        spdlog::shutdown();
    }

    PipelineLogger::~PipelineLogger()
    {
        stopPipelineLogger();
    }

    void PipelineLogger::setLevel(int level)
    {
        spdlog::set_level(static_cast<spdlog::level::level_enum>(level));
    }

} // namespace DslPipelineServer