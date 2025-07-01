/********************************************
// Filename: dsl_common.h
// Created by zhaojiadi on 2023/4/29
// Description:

********************************************/
#pragma once
#include <glib.h>
#include <functional>
#include <iostream>
#include "common/non_copyable.h"

namespace DslPipelineServer
{

    class DslThread : public NonCopyable
    {
    public:
        using ThreadFunction = std::function<void()>;
        DslThread(ThreadFunction func) : threadFunc(func), threadId(nullptr) {}

        void start()
        {
            if (threadId)
            {
                std::cerr << "Thread already started!" << std::endl;
                return;
            }

            threadId = g_thread_new("DslThread", threadFuncWrapper, this);
            if (!threadId)
            {
                std::cerr << "Failed to create thread!" << std::endl;
            }
        }

        void join()
        {
            if (!threadId)
            {
                std::cerr << "Thread not started or already joined!" << std::endl;
                return;
            }

            g_thread_join(threadId);
            threadId = nullptr;
        }

        bool isRunning() const
        {
            return threadId != nullptr;
        }

        ~DslThread()
        {
            if (threadId) {
                std::cerr << "Thread not joined, calling join in destructor." << std::endl;
                join();
            }
        }

    private:
        ThreadFunction threadFunc;
        GThread* threadId;

        static gpointer threadFuncWrapper(gpointer data)
        {
            DslThread* wrapper = static_cast<DslThread*>(data);
            if (wrapper && wrapper->threadFunc)
            {
                wrapper->threadFunc();
            }
            return nullptr;
        }
    };

} // namespace DslPipelineServer