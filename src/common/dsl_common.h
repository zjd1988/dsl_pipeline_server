/********************************************
// Filename: dsl_common.h
// Created by zhaojiadi on 2023/4/29
// Description:

********************************************/
#pragma once
#include <set>
#include <string>

namespace DslPipelineServer
{

    extern std::set<std::string> gSupportedVideoFormat;
    extern std::wstring convertStrToWStr(const std::string& str);
    extern std::string convertWStrToStr(const std::wstring& w_str);

} // namespace DslPipelineServer