/********************************************
// Filename: dsl_common.cpp
// Created by zhaojiadi on 2023/4/29
// Description:

********************************************/
#include <locale>
#include <codecvt>
#include "common/dsl_common.h"

namespace DslPipelineServer
{

    std::set<std::string> gSupportedVideoFormat = {"I420", "NV12", "RGBA", "YUY2", "YVYU"};

    std::wstring convertStrToWStr(const std::string& str)
    {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        std::wstring wide_str = converter.from_bytes(str);
        return wide_str;
    }

    std::string convertWStrToStr(const std::wstring& w_str)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> strCnv;
        return strCnv.to_bytes(w_str);
    }

} // namespace DslPipelineServer