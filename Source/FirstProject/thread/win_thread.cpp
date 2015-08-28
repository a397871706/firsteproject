#include "stdafx.h"
#include "win_thread.h"
#include "message_loop.h"

#include <process.h>
#include <assert.h>

namespace
{
const DWORD kVCThreadNameException = 0x406D1388;
}

WinThread::WinThread(const std::string& thread_name)
    : handle_()
    , name_(thread_name)
    , priority_(T_PRIORITY::NORMAL)
    , thread_id_(0)
    , isrunning_(false)
    , messgae_loop(new MessageLoop())
{
    ::CreateEvent(NULL, FALSE, FALSE, NULL);
}

WinThread::~WinThread()
{
    isrunning_ = false;
    if (handle_)
        ::CloseHandle(handle_);
}

void WinThread::Start()
{
    isrunning_ = true;
    handle_ = (HANDLE)_beginthreadex(NULL, 0, ThreadMain, this, NULL, 
                                     &thread_id_);
}

void WinThread::Stop()
{
    isrunning_ = false;
}

void WinThread::SetPriority(T_PRIORITY priority)
{
    ::SetThreadPriority(handle_, priority);
}

void WinThread::Run()
{
    while (true)
    {
        if (!isrunning_)
            break;
        
        messgae_loop->Loop();
    }
}

unsigned int  WinThread::ThreadMain(void* thread)
{
    WinThread*th = reinterpret_cast<WinThread*>(thread);
    assert(th);
    if (th)
    {
        th->SetThreadName();
        th->Run();
    }

    return 0;
}

void WinThread::SetThreadName()
{
    THREADNAME_INFO info = {};
    info.dwType = 0x1000;
    info.szName = name_.c_str();
    info.dwThreadID = thread_id_;
    info.dwFlags = 0;

    __try
    {
        RaiseException(kVCThreadNameException, 0, sizeof(info) / sizeof(DWORD),
                       reinterpret_cast<DWORD_PTR*>(&info));
    }
    __except (EXCEPTION_CONTINUE_EXECUTION) 
    {}
}

void WinThread::AddTask(const CallBack& callback)
{
    assert(messgae_loop);
    if (messgae_loop)
        messgae_loop->AddTask(callback);
}

DWORD WinThread::SuspendThread()
{
    return ::SuspendThread(handle_);
}

DWORD WinThread::ResumeThread()
{
    return ::ResumeThread(handle_);
}
