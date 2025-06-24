/********************************************
// Filename: sink_config.h
// Created by zhaojiadi on 2023/4/29
// Description:

********************************************/
#pragma once
#include <map>
#include <vector>
#include <string>
#include <yaml-cpp/yaml.h>

namespace DslPipelineServer
{

    typedef enum SinkCompType
    {
        INVALID_SINK_COMP_TYPE                         = -1,
        APP_SINK_COMP_TYPE                             = 0,      // allows the application to receive buffers or samples from a DSL Pipeline.
        V4L2_SINK_COMP_TYPE                            = 0,      // streams video to a V4L2 device or v4l2loopback
        FILE_SINK_COMP_TYPE                            = 1,      // encodes video to a media container file
        RECORD_SINK_COMP_TYPE                          = 2,      // similar to the File sink but with Start/Stop/Duration control and a cache for pre-start buffering
        RTMP_SINK_COMP_TYPE                            = 3,      // streams encoded video using the Real-time Messaging Protocol (RTMP) to social media networks, live streaming platforms, and media servers
        RTSP_CLIENT_SINK_COMP_TYPE                     = 4,      // streams encoded video using the Real-time Streaming Protocol (RTSP) as a client of a media server
        RTSP_SERVER_SINK_COMP_TYPE                     = 5,      // streams encoded video via an RTSP (UDP) Server on a specified port
        MAX_SINK_COMP_TYPE,
    } SinkCompType;

    typedef struct AppSinkComConfig
    {
        uint32_t                                       data_type;           // either `DSL_SINK_APP_DATA_TYPE_SAMPLE` or `DSL_SINK_APP_DATA_TYPE_BUFFER`
    } AppSinkComConfig;

    typedef struct V4l2SinkCompConfig
    {
        std::string                                    device_location;     // device-location setting for the V4L2 Sink
    } V4l2SinkCompConfig;

    typedef struct FileSinkCompConfig
    {
        std::string                                    file_path;           // absolute or relative filespec for the media file to write to.
        uint32_t                                       encoder;             // one of the Encoder Types defined above.
        uint32_t                                       container;           // one of the Video Container Types defined above.
        uint32_t                                       bitrate;             // bitrate for video encoding in units of bit/s. Set to 0 to use the encoder's default.
        uint32_t                                       iframe_interval;     // intra frame (key-frame) occurrence interval.
    } FileSinkCompConfig;

    typedef struct RecordSinkCompConfig
    {
        std::string                                    out_dir;             // absolute or relative pathspec for the directory to save the recorded video streams.
        uint32_t                                       encoder;             // one of the Encoder Types defined above.
        uint32_t                                       container;           // one of the Video Container Types defined above.
        uint32_t                                       bitrate;             // bitrate for video encoding in units of bit/s. Set to 0 to use the encoder's default.
        uint32_t                                       iframe_interval;     // intra frame (key-frame) occurrence interval.
    } RecordSinkCompConfig;

    typedef struct RtmpSinkCompConfig
    {
        std::string                                    uri;                 // the RTMP URI to stream to.
        uint32_t                                       bitrate;             // bitrate for video encoding in units of bit/s. Set to 0 to use the encoder's default.
        uint32_t                                       iframe_interval;     // intra frame (key-frame) occurrence interval.
    } RtmpSinkCompConfig;

    typedef struct RtspClientSinkCompConfig
    {
        std::string                                    uri;                 // the RTSP URI to stream to.
        uint32_t                                       encoder;             // one of the Encoder Types defined above.
        uint32_t                                       bitrate;             // bitrate for video encoding in units of bit/s. Set to 0 to use the encoder's default (4Mbps).
        uint32_t                                       iframe_interval;     // intra frame (key-frame) occurrence interval.
    } RtspClientSinkCompConfig;

    typedef struct RtspServerSinkCompConfig
    {
        std::string                                    host;                // host name
        uint32_t                                       udp_port;            // UDP port setting for the RTSP server.
        uint32_t                                       rtsp_port;           // RTSP port setting for the RTSP server.
        uint32_t                                       encoder;             // one of the Encoder Types defined above.
        uint32_t                                       bitrate;             // bitrate for video encoding in units of bit/s. Set to 0 to use the encoder's default.
        uint32_t                                       iframe_interval;     // intra frame (key-frame) occurrence interval.
    } RtspServerSinkCompConfig;

    typedef struct SinkCompConfig
    {
        SinkCompType                                   type;
        union
        {
            AppSinkComConfig                           app_config;
            V4l2SinkCompConfig                         v4l2_config;
            FileSinkCompConfig                         file_config;
            RecordSinkCompConfig                       record_config;
            RtmpSinkCompConfig                         rtmp_config;
            RtspClientSinkCompConfig                   rtsp_client_config;
            RtspServerSinkCompConfig                   rtsp_server_config;
        };
    } SinkCompConfig;

    void logValidSinkCompType();
    int convertStrToSinkCompType(const std::string type_str, SinkCompType& type);
    int convertSinkCompTypeToStr(const SinkCompType type, std::string& type_str);
    int parseSinkCompConfigFromNode(const YAML::Node& node, SinkCompConfig& config);
    int dumpSinkCompConfigToNode(const SinkCompConfig& config, YAML::Node& node);
    extern std::map<std::string, SinkCompType> gStrToSinkCompType;
    extern std::map<SinkCompType, std::string> gSinkCompTypeToStr;

} // namespace DslPipelineServer