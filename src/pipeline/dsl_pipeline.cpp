/********************************************
// Filename: dsl_pipeline.cpp
// Created by zhaojiadi on 2022/10/17
// Description:

********************************************/
#include <locale>
#include <codecvt>
#include "DslApi.h"
#include "common/logger.h"
#include "pipeline/dsl_pipeline.h"

namespace DslPipelineServer
{

    static std::wstring convertStrToWStr(const std::string& str)
    {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        std::wstring wide_str = converter.from_bytes(str);
        return wide_str;
    }

    DslPipeline::DslPipeline(const PipelineConfig& config)
    {
        m_name = config.name;
        if (0 != createComponents(config))
        {
            return;
        }
        m_init_flag = true;
    }

    int DslPipeline::dslSourceComponentCreate(const std::string name, const SourceCompConfig& config)
    {
        int ret = 0;
        auto type = config.type;
        std::string type_str;
        if (0 != convertSourceCompTypeToStr(type, type_str))
        {
            PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "invalid source component type: {} ", type);
            logValidSourceCompType();
            return -1;
        }
        std::wstring w_name = convertStrToWStr(name);
        switch (type)
        {
            case APP_SOURCE_COMP_TYPE:
            {
                auto app_config = config.app_config;
                std::string buffer_in_format = app_config.buffer_in_format;
                std::wstring w_buffer_in_format = convertStrToWStr(buffer_in_format);
                ret = (int)dsl_source_app_new(w_name.c_str(), app_config.is_live, w_buffer_in_format.c_str(), app_config.width, 
                    app_config.height, app_config.fps_n, app_config.fps_d);
                break;
            }
            case CSI_SOURCE_COMP_TYPE:
            {
                auto csi_config = config.csi_config;
                ret = (int)dsl_source_csi_new(w_name.c_str(), csi_config.width, csi_config.height, csi_config.fps_n, csi_config.fps_d);
                break;
            }
            case V4L2_SOURCE_COMP_TYPE:
            {
                auto v4l2_config = config.v4l2_config;
                std::string device_location = v4l2_config.device_location;
                std::wstring w_device_location = convertStrToWStr(w_device_location);
                ret = (int)dsl_source_v4l2_new(w_name.c_str(), w_device_location.c_str());
                break;
            }
            case URI_SOURCE_COMP_TYPE:
            {
                auto uri_config = config.uri_config;
                std::string uri = uri_config.uri;
                std::wstring w_uri = convertStrToWStr(uri);
                ret = (int)dsl_source_uri_new(w_name.c_str(), w_uri.c_str(), uri_config.is_live, 
                    uri_config.skip_frames, uri_config.drop_frame_interval);
                break;
            }
            case FILE_SOURCE_COMP_TYPE:
            {
                auto file_config = config.file_config;
                std::string file_path = file_config.file_path;
                std::wstring w_file_path = convertStrToWStr(file_path);
                ret = (int)dsl_source_file_new(w_name.c_str(), w_file_path.c_str(), file_config.repeat_enabled);
                break;
            }
            case RTSP_SOURCE_COMP_TYPE:
            {
                auto rtsp_config = config.rtsp_config;
                std::string uri = rtsp_config.uri;
                std::wstring w_uri = convertStrToWStr(uri);
                ret = (int)dsl_source_rtsp_new(w_name.c_str(), w_uri.c_str(), rtsp_config.protocol, rtsp_config.skip_frames, 
                    rtsp_config.dropFrameInterval, rtsp_config.latency, rtsp_config.timeout);
                break;
            }
            default:
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "current not support source component type: {} ", type_str);
                return -1;
            }
        }
        return ret;
    }

    int DslPipeline::dslInferComponentCreate(const std::string name, const InferCompConfig& config)
    {
        int ret = 0;
        auto type = config.type;
        std::string type_str;
        if (0 != convertInferCompTypeToStr(type, type_str))
        {
            PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "invalid infer component type: {} ", type);
            logValidInferCompType();
            return -1;
        }
        std::wstring w_name = convertStrToWStr(name);
        switch (type)
        {
            case PRIMARY_GIE_INFER_COMP_TYPE:
            {
                auto gie_config = config.primary_gie_config;
                std::string config_file = gie_config.config_file;
                std::wstring w_config_file = convertStrToWStr(config_file);
                std::string engine_file = gie_config.engine_file;
                std::wstring w_engine_file = convertStrToWStr(engine_file);
                ret = (int)dsl_infer_gie_primary_new(w_name.c_str(), w_config_file.c_str(), w_engine_file.c_str(), gie_config.interval);
                break;
            }
            case SECONDARY_GIE_INFER_COMP_TYPE:
            {
                auto gie_config = config.secondary_gie_config;
                std::string config_file = gie_config.config_file;
                std::wstring w_config_file = convertStrToWStr(config_file);
                std::string engine_file = gie_config.engine_file;
                std::wstring w_engine_file = convertStrToWStr(engine_file);
                std::string infer_on_gie = gie_config.infer_on_gie;
                std::wstring w_infer_on_gie = convertStrToWStr(infer_on_gie);
                ret = (int)dsl_infer_gie_secondary_new(w_name.c_str(), w_config_file.c_str(), w_engine_file.c_str(), 
                    w_infer_on_gie.c_str(), gie_config.interval);
                break;
            }
            case PRIMARY_TIS_INFER_COMP_TYPE:
            {
                auto tis_config = config.primary_tis_config;
                std::string config_file = tis_config.config_file;
                std::wstring w_config_file = convertStrToWStr(config_file);
                ret = (int)dsl_infer_tis_primary_new(w_name.c_str(), w_config_file.c_str(), tis_config.interval);
                break;
            }
            case SECONDARY_TIS_INFER_COMP_TYPE:
            {
                auto tis_config = config.secondary_tis_config;
                std::string config_file = tis_config.config_file;
                std::wstring w_config_file = convertStrToWStr(config_file);
                std::string infer_on_tis = tis_config.infer_on_tis;
                std::wstring w_infer_on_tis = convertStrToWStr(infer_on_tis);
                ret = (int)dsl_infer_tis_secondary_new(w_name.c_str(), w_config_file.c_str(), w_infer_on_tis.c_str(), 
                    tis_config.interval);
                break;
            }
            default:
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "current not support infer component type: {} ", type_str);
                return -1;
            }
        }
        return 0;
    }

    int DslPipeline::dslTrackerComponentCreate(const std::string name, const TrackerCompConfig& config)
    {
        return 0;
    }

    int DslPipeline::dslOsdComponentCreate(const std::string name, const OsdCompConfig& config)
    {
        return 0;
    }

    int DslPipeline::dslSinkComponentCreate(const std::string name, const SinkCompConfig& config)
    {
        int ret = 0;
        auto type = config.type;
        std::string type_str;
        if (0 != convertSinkCompTypeToStr(type, type_str))
        {
            PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "invalid sink component type: {} ", type);
            logValidSinkCompType();
            return -1;
        }
        std::wstring w_name = convertStrToWStr(name);
        switch (type)
        {
            case APP_SINK_COMP_TYPE:
            {
                auto app_config = config.app_config;
                std::string buffer_in_format = app_config.buffer_in_format;
                std::wstring w_buffer_in_format = convertStrToWStr(buffer_in_format);
                ret = (int)dsl_source_app_new(w_name.c_str(), app_config.is_live, w_buffer_in_format.c_str(), app_config.width, 
                    app_config.height, app_config.fps_n, app_config.fps_d);
                break;
            }
            case V4L2_SINK_COMP_TYPE:
            {
                auto csi_config = config.csi_config;
                ret = (int)dsl_source_csi_new(w_name.c_str(), csi_config.width, csi_config.height, csi_config.fps_n, csi_config.fps_d);
                break;
            }
            case FILE_SINK_COMP_TYPE:
            {
                auto v4l2_config = config.v4l2_config;
                std::string device_location = v4l2_config.device_location;
                std::wstring w_device_location = convertStrToWStr(w_device_location);
                ret = (int)dsl_source_v4l2_new(w_name.c_str(), w_device_location.c_str());
                break;
            }
            case RECORD_SINK_COMP_TYPE:
            {
                auto uri_config = config.uri_config;
                std::string uri = uri_config.uri;
                std::wstring w_uri = convertStrToWStr(uri);
                ret = (int)dsl_source_uri_new(w_name.c_str(), w_uri.c_str(), uri_config.is_live, 
                    uri_config.skip_frames, uri_config.drop_frame_interval);
                break;
            }
            case RTMP_SINK_COMP_TYPE:
            {
                auto file_config = config.file_config;
                std::string file_path = file_config.file_path;
                std::wstring w_file_path = convertStrToWStr(file_path);
                ret = (int)dsl_source_file_new(w_name.c_str(), w_file_path.c_str(), file_config.repeat_enabled);
                break;
            }
            case RTSP_CLIENT_SINK_COMP_TYPE:
            {
                auto rtsp_config = config.rtsp_config;
                std::string uri = rtsp_config.uri;
                std::wstring w_uri = convertStrToWStr(uri);
                ret = (int)dsl_source_rtsp_new(w_name.c_str(), w_uri.c_str(), rtsp_config.protocol, rtsp_config.skip_frames, 
                    rtsp_config.dropFrameInterval, rtsp_config.latency, rtsp_config.timeout);
                break;
            }
            case RTSP_SERVER_SINK_COMP_TYPE:
            {
                auto rtsp_config = config.rtsp_config;
                std::string uri = rtsp_config.uri;
                std::wstring w_uri = convertStrToWStr(uri);
                ret = (int)dsl_source_rtsp_new(w_name.c_str(), w_uri.c_str(), rtsp_config.protocol, rtsp_config.skip_frames, 
                    rtsp_config.dropFrameInterval, rtsp_config.latency, rtsp_config.timeout);
                break;
            }
            default:
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "current not support source component type: {} ", type_str);
                return -1;
            }
        }
        return ret;
    }

    int DslPipeline::createComponents(const PipelineConfig& config)
    {
        int ret = 0;
        for (size_t index = 0; index < config.component_names.size(); index++)
        {
            std::string comp_name = config.component_names[index];
            if (config.component_configs.end() == config.component_configs.find(comp_name))
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "cannot find component: {} config info", comp_name);
                return -1;
            }

            auto& comp_config = config.component_configs[comp_name];
            if (comp_config.name != comp_name)
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "component name: {} in config info not equal to expect: {}", 
                    comp_config.name, comp_name);
                return -1;
            }
            auto comp_type = comp_config.type;
            std::string comp_type_str;
            if (0 != convertComponentTypeToStr(comp_type, comp_type_str))
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "invalid component type: {} ", comp_type);
                logValidPipelineCompType();
                return -1;
            }
            switch (comp_type)
            {
                case SOURCE_COMPONENT_TYPE:
                {
                    ret = dslSourceComponentCreate(comp_name, comp_config.source_config);
                    break;
                }
                case INFER_COMPONENT_TYPE:
                {
                    ret = dslInferComponentCreate(comp_name, comp_config.infer_config);
                    break;
                }
                case TRACKER_COMPONENT_TYPE:
                {
                    ret = dslTrackerComponentCreate(comp_name, comp_config.tracker_config);
                    break;
                }
                case OSD_COMPONENT_TYPE:
                {
                    ret = dslOsdComponentCreate(comp_name, comp_config.osd_config);
                    break;
                }
                case SINK_COMPONENT_TYPE:
                {
                    ret = dslSinkComponentCreate(comp_name, comp_config.sink_config);
                    break;
                }
                default:
                {
                    PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "current not support create component type: {} for {}", comp_type_str, comp_name);
                    return -1;
                }
            }
            if (0 != ret)
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "create component: {} fail", comp_name);
                break;
            }
        }
        return ret;
    }

} // namespace DslPipelineServer