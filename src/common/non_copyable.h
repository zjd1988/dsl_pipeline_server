/********************************************
// Filename: non_copyable.h
// Created by zhaojiadi on 2023/4/29
// Description:

********************************************/
#pragma once

namespace DslPipelineServer
{

    /** protocol class. used to delete assignment operator. */
    class NonCopyable
    {
    public:
        NonCopyable()                    = default;
        NonCopyable(const NonCopyable&)  = delete;
        NonCopyable(const NonCopyable&&) = delete;
        NonCopyable& operator=(const NonCopyable&) = delete;
        NonCopyable& operator=(const NonCopyable&&) = delete;
    };

} // namespace DslPipelineServer