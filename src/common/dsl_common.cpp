/********************************************
// Filename: dsl_common.cpp
// Created by zhaojiadi on 2023/4/29
// Description:

********************************************/
#include "common/dsl_common.h"

namespace DslPipelineServer
{

    std::set<std::string> gSupportedVideoFormat = {"I420", "NV12", "RGBA", "YUY2", "YVYU"};

} // namespace DslPipelineServer