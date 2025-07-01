/********************************************
// Filename: source_config.h
// Created by zhaojiadi on 2023/4/29
// Description:

********************************************/
#pragma once
#include <map>
#include <vector>
#include <string>
#include <yaml-cpp/yaml.h>
#include "component/base_config.h"

namespace DslPipelineServer
{

    typedef enum SourceCompType
    {
        INVALID_SOUCE_COMP_TYPE                         = -1,
        APP_SOURCE_COMP_TYPE                            = 0,      // Allows the application to insert raw samples or buffers into a DSL Pipeline
        CSI_SOURCE_COMP_TYPE                            = 1,      // Camera Serial Interface (CSI) Source - Jetson platform only
        V4L2_SOURCE_COMP_TYPE                           = 2,      // Stream from any V4L2 compatable device - a USB Webcam for example
        URI_SOURCE_COMP_TYPE                            = 3,      // Uniform Resource Identifier ( URI ) Source
        FILE_SOURCE_COMP_TYPE                           = 4,      // Derived from URI Source with fixed inputs
        RTSP_SOURCE_COMP_TYPE                           = 5,      // Real-time Streaming Protocol ( RTSP ) Source - supports transport over TCP or UDP in unicast or multicast mode
        MAX_SOURCE_COMP_TYPE,
    } SourceCompType;

    typedef struct AppSourceCompConfig
    {
        bool                                            is_live;           // set to true to instruct the source to behave like a live source. This includes that it will only push out buffers in the PLAYING state.
        std::string                                     buffer_in_format;  // one of the DSL_BUFFER_FORMAT constants.
        uint32_t                                        width;             // width of the source in pixels
        uint32_t                                        height;            // height of the source in pixels
        uint32_t                                        fps_n;             // frames per second fraction numerator
        uint32_t                                        fps_d;             // frames per second fraction denominator
    } AppSourceCompConfig;

    typedef struct CsiSourceCompConfig
    {
        uint32_t                                        width;             // width of the source in pixels
        uint32_t                                        height;            // height of the source in pixels
        uint32_t                                        fps_n;             // frames per second fraction numerator
        uint32_t                                        fps_d;             // frames per second fraction denominator
    } CsiSourceCompConfig;

    typedef struct V4l2SourceCompConfig
    {
        std::string                                     device_location;   // device location for the new Source (/dev/video0 for example)
    } V4l2SourceCompConfig;

    typedef struct UriSourceCompConfig
    {
        std::string                                     uri;                  // fully qualified URI prefixed with http://, https://, or file://
        bool                                            is_live;              // true if the URI is a live source, false otherwise. File URI's will use a fixed value of false
        uint32_t                                        skip_frames;          // the type of frames to skip during decoding.
                                                                              // (0): decode_all - Decode all frames
                                                                              // (1): decode_non_ref - Decode non-ref frame
                                                                              // (2): decode_key - decode key frames
        uint32_t                                        drop_frame_interval;  // number of frames to drop between each decoded frame. 0 = decode all frames
    } UriSourceCompConfig;

    typedef struct FileSourceCompConfig
    {
        std::string                                     file_path;            // absolute or relative path to the file to play
        bool                                            repeat_enabled;       // set to true to repeat the file on end-of-stream (EOS), false otherwise
    } FileSourceCompConfig;

    typedef struct RtspSourceCompConfig
    {
        std::string                                     uri;                  // fully qualified URI prefixed with rtsp://
        uint32_t                                        protocol;             // one of the RTP Protocols constant values.
        uint32_t                                        skip_frames;          // the type of frames to skip during decoding.
                                                                              // (0): decode_all - Decode all frames
                                                                              // (1): decode_non_ref - Decode non-ref frame
                                                                              // (2): decode_key - decode key frames
        uint32_t                                        drop_frame_interval;  // number of frames to drop between each decoded frame. 0 = decode all frames.
        uint32_t                                        latency;              // source latency setting in milliseconds, equates to the amount of data to buffer.
        uint32_t                                        timeout;              // maximum time between successive frame buffers in units of seconds before initiating a "reconnection-cycle". Set to 0 to disable the timeout.
    } RtspSourceCompConfig;

    typedef struct SourceCompConfig : public BaseCompConfig
    {
        SourceCompType                                  source_type;
        AppSourceCompConfig                             app_config;
        CsiSourceCompConfig                             csi_config;
        V4l2SourceCompConfig                            v4l2_config;
        UriSourceCompConfig                             uri_config;
        FileSourceCompConfig                            file_config;
        RtspSourceCompConfig                            rtsp_config;
    } SourceCompConfig;

    void logValidSourceCompType();
    int convertStrToSourceCompType(const std::string type_str, SourceCompType& type);
    int convertSourceCompTypeToStr(const SourceCompType type, std::string& type_str);
    void parseSourceCompConfigFromNode(const YAML::Node& node, SourceCompConfig& config);
    void dumpSourceCompConfigToNode(const SourceCompConfig& config, YAML::Node& node);
    extern std::map<std::string, SourceCompType> gStrToSourceCompType;
    extern std::map<SourceCompType, std::string> gSourceCompTypeToStr;

} // namespace DslPipelineServer