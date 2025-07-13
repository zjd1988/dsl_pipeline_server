/********************************************
// Filename: logger.h
// Created by zhaojiadi on 2023/4/29
// Description:

********************************************/
/*
日志等级：trace, debug, info, warn, err, critical
使用方法：包含log.h头文件,调用初始化函数,使用PIPELINE_LOG等打印日志信息
例：
PipelineLogger::Instance().InitServerLog("scenario_edit", "scenario_edit_log.txt");
int i = 10;
double d_number = 10.01;
PIPELINE_LOG(PIPELINE_LOG_LEVEL_DEBUG, "server log message");
PIPELINE_LOG(PIPELINE_LOG_LEVEL_DEBUG, "server log message #{0}, d_number:{1}", i, d_number);
注：使用{}格式化字符串，里面的数字为占位符
https://github.com/gabime/spdlog

spdlog::info("Welcome to spdlog!");
spdlog::error("Some error message with arg: {}", 1);

spdlog::warn("Easy padding in numbers like {:08d}", 12);
spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
spdlog::info("Support for floats {:03.2f}", 1.23456);
spdlog::info("Positional args are {1} {0}..", "too", "supported");
spdlog::info("{:<30}", "left aligned");

spdlog::set_level(spdlog::level::debug); // Set global log level to debug
spdlog::debug("This message should be displayed..");

*/
#pragma once
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <iostream>
#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/fmt/bin_to_hex.h"
#include "common/non_copyable.h"

#define PIPELINE_LOG_LEVEL_TRACE    SPDLOG_LEVEL_TRACE
#define PIPELINE_LOG_LEVEL_DEBUG    SPDLOG_LEVEL_DEBUG
#define PIPELINE_LOG_LEVEL_INFO     SPDLOG_LEVEL_INFO
#define PIPELINE_LOG_LEVEL_WARN     SPDLOG_LEVEL_WARN
#define PIPELINE_LOG_LEVEL_ERROR    SPDLOG_LEVEL_ERROR
#define PIPELINE_LOG_LEVEL_FATAL    SPDLOG_LEVEL_CRITICAL
#define PIPELINE_LOG_LEVEL_OFF      SPDLOG_LEVEL_OFF

#define PIPELINE_LOG_TRACE(...)       SPDLOG_TRACE(__VA_ARGS__)
#define PIPELINE_LOG_DEBUG(...)       SPDLOG_DEBUG(__VA_ARGS__)
#define PIPELINE_LOG_INFO(...)        SPDLOG_INFO(__VA_ARGS__)
#define PIPELINE_LOG_WARN(...)        SPDLOG_WARN(__VA_ARGS__)
#define PIPELINE_LOG_ERROR(...)       SPDLOG_ERROR(__VA_ARGS__)
#define PIPELINE_LOG_CRITICAL(...)    SPDLOG_CRITICAL(__VA_ARGS__)


#define PIPELINE_LOG_IMPL(level, ...)                                               \
do {                                                                                \
    auto logger = DslPipelineServer::PipelineLogger::Instance().getLogger();        \
    if (nullptr == logger)                                                          \
        logger = spdlog::default_logger_raw();                                      \
    switch(level)                                                                   \
    {                                                                               \
        case PIPELINE_LOG_LEVEL_TRACE:                                              \
            SPDLOG_LOGGER_TRACE(logger, __VA_ARGS__);                               \
            break;                                                                  \
        case PIPELINE_LOG_LEVEL_DEBUG:                                              \
            SPDLOG_LOGGER_DEBUG(logger, __VA_ARGS__);                               \
            break;                                                                  \
        case PIPELINE_LOG_LEVEL_INFO:                                               \
            SPDLOG_LOGGER_INFO(logger, __VA_ARGS__);                                \
            break;                                                                  \
        case PIPELINE_LOG_LEVEL_WARN:                                               \
            SPDLOG_LOGGER_WARN(logger, __VA_ARGS__);                                \
            break;                                                                  \
        case PIPELINE_LOG_LEVEL_ERROR:                                              \
            SPDLOG_LOGGER_ERROR(logger, __VA_ARGS__);                               \
            break;                                                                  \
        case PIPELINE_LOG_LEVEL_FATAL:                                              \
            SPDLOG_LOGGER_CRITICAL(logger, __VA_ARGS__);                            \
            break;                                                                  \
        case PIPELINE_LOG_LEVEL_OFF:                                                \
            break;                                                                  \
        default:                                                                    \
            SPDLOG_LOGGER_CRITICAL(logger, __VA_ARGS__);                            \
    }                                                                               \
} while(0)


#define PIPELINE_LOG(level, ...)  PIPELINE_LOG_IMPL(level, ##__VA_ARGS__)

namespace DslPipelineServer
{

    class PipelineLogger : public NonCopyable
    {
    public:
        static PipelineLogger& Instance();

        void initPipelineLogger(std::string file_name, int log_level = spdlog::level::trace);

        void stopPipelineLogger();

        void setLevel(int level = spdlog::level::trace);

        spdlog::logger* getLogger()
        {
            if (nullptr == m_logger.get())
            {
                std::string log_path;
                int log_level = PIPELINE_LOG_LEVEL_INFO;
                initPipelineLogger(log_path, log_level);
            }
            return m_logger.get();
        }

    private:
        PipelineLogger();
        ~PipelineLogger();

    private:
        std::shared_ptr<spdlog::logger> m_logger;
    };

}  // namespace DslPipelineServer