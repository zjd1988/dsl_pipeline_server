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

    DslPipeline::DslPipeline(const PipelineConfig& config, const std::string name)
    {
        m_name = config.name;
        if ("" != name)
            m_name = name;
        if (0 != createComponents(config))
            return;
        m_init_flag = true;
    }

    DslPipeline::~DslPipeline()
    {
        return;
    }

    int DslPipeline::dslSourceComponentCreate(const std::string name, const SourceCompConfig& config)
    {
        int ret = 0;
        auto type = config.source_type;
        std::string type_str;
        if (0 != convertSourceCompTypeToStr(type, type_str))
        {
            PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "invalid source component type: {} ", int(type));
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
                std::wstring w_device_location = convertStrToWStr(device_location);
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
                    rtsp_config.drop_frame_interval, rtsp_config.latency, rtsp_config.timeout);
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
        auto type = config.infer_type;
        std::string type_str;
        if (0 != convertInferCompTypeToStr(type, type_str))
        {
            PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "invalid infer component type: {} ", int(type));
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
        int ret = 0;
        std::wstring w_name = convertStrToWStr(name);
        std::string config_file = config.config_file;
        std::wstring w_config_file = convertStrToWStr(config_file);
        ret = (int)dsl_tracker_new(w_name.c_str(), w_config_file.c_str(), config.height, config.width);
        return ret;
    }

    int DslPipeline::dslOsdComponentCreate(const std::string name, const OsdCompConfig& config)
    {
        int ret = 0;
        std::wstring w_name = convertStrToWStr(name);
        ret = (int)dsl_osd_new(w_name.c_str(), config.text_enable, config.clock_enable, config.bbox_enable, config.mask_enable);
        return ret;
    }

    int DslPipeline::dslSinkComponentCreate(const std::string name, const SinkCompConfig& config)
    {
        int ret = 0;
        auto type = config.sink_type;
        std::string type_str;
        if (0 != convertSinkCompTypeToStr(type, type_str))
        {
            PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "invalid sink component type: {} ", int(type));
            logValidSinkCompType();
            return -1;
        }
        std::wstring w_name = convertStrToWStr(name);
        switch (type)
        {
            case APP_SINK_COMP_TYPE:
            {
                auto app_config = config.app_config;
                ret = (int)dsl_sink_app_new(w_name.c_str(), app_config.data_type, nullptr, nullptr);
                break;
            }
            case V4L2_SINK_COMP_TYPE:
            {
                auto v4l2_config = config.v4l2_config;
                std::string device_location = v4l2_config.device_location;
                std::wstring w_device_location = convertStrToWStr(device_location);
                ret = (int)dsl_sink_v4l2_new(w_name.c_str(), w_device_location.c_str());
                break;
            }
            case FILE_SINK_COMP_TYPE:
            {
                auto file_config = config.file_config;
                std::string file_path = file_config.file_path;
                std::wstring w_file_path = convertStrToWStr(file_path);
                ret = (int)dsl_sink_file_new(w_name.c_str(), w_file_path.c_str(), file_config.encoder, file_config.container, 
                    file_config.bitrate, file_config.iframe_interval);
                break;
            }
            case RECORD_SINK_COMP_TYPE:
            {
                auto record_config = config.record_config;
                std::string out_dir = record_config.out_dir;
                std::wstring w_out_dir = convertStrToWStr(out_dir);
                ret = (int)dsl_sink_record_new(w_name.c_str(), w_out_dir.c_str(), record_config.encoder, record_config.container, 
                    record_config.bitrate, record_config.iframe_interval, nullptr);
                break;
            }
            case RTMP_SINK_COMP_TYPE:
            {
                auto rtmp_config = config.rtmp_config;
                std::string uri = rtmp_config.uri;
                std::wstring w_uri = convertStrToWStr(uri);
                ret = (int)dsl_sink_rtmp_new(w_name.c_str(), w_uri.c_str(), rtmp_config.encoder, rtmp_config.bitrate, 
                    rtmp_config.iframe_interval);
                break;
            }
            case RTSP_CLIENT_SINK_COMP_TYPE:
            {
                auto rtsp_client_config = config.rtsp_client_config;
                std::string uri = rtsp_client_config.uri;
                std::wstring w_uri = convertStrToWStr(uri);
                ret = (int)dsl_sink_rtsp_client_new(w_name.c_str(), w_uri.c_str(), rtsp_client_config.encoder, 
                    rtsp_client_config.bitrate, rtsp_client_config.iframe_interval);
                break;
            }
            case RTSP_SERVER_SINK_COMP_TYPE:
            {
                auto rtsp_server_config = config.rtsp_server_config;
                std::string host = rtsp_server_config.host;
                std::wstring w_host = convertStrToWStr(host);
                ret = (int)dsl_sink_rtsp_server_new(w_name.c_str(), w_host.c_str(), rtsp_server_config.udp_port, 
                    rtsp_server_config.rtsp_port, rtsp_server_config.encoder, rtsp_server_config.bitrate, 
                    rtsp_server_config.iframe_interval);
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
        for (size_t index = 0; index < config.component_configs.size(); index++)
        {
            auto& comp_config = config.component_configs[index];
            auto comp_name = comp_config->comp_name;
            auto comp_type = comp_config->comp_type;
            std::string comp_type_str;
            if (0 != convertComponentTypeToStr(comp_type, comp_type_str))
            {
                PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "{} have invalid component type: {} ", comp_name, int(comp_type));
                logValidPipelineCompType();
                return -1;
            }
            switch (comp_type)
            {
                case SOURCE_COMPONENT_TYPE:
                {
                    ret = dslSourceComponentCreate(comp_name, *(SourceCompConfig*)comp_config.get());
                    break;
                }
                case INFER_COMPONENT_TYPE:
                {
                    ret = dslInferComponentCreate(comp_name, *(InferCompConfig*)comp_config.get());
                    break;
                }
                case TRACKER_COMPONENT_TYPE:
                {
                    ret = dslTrackerComponentCreate(comp_name, *(TrackerCompConfig*)comp_config.get());
                    break;
                }
                case OSD_COMPONENT_TYPE:
                {
                    ret = dslOsdComponentCreate(comp_name, *(OsdCompConfig*)comp_config.get());
                    break;
                }
                case SINK_COMPONENT_TYPE:
                {
                    ret = dslSinkComponentCreate(comp_name, *(SinkCompConfig*)comp_config.get());
                    break;
                }
                default:
                {
                    PIPELINE_LOG(PIPELINE_LOG_LEVEL_ERROR, "{} has invalid component type: {}", comp_name, comp_type_str);
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