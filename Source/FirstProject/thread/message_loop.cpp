#include "stdafx.h"
#include "message_loop.h"

MessageLoop::MessageLoop()
    : message_()
    , lock_()
    , hEvent_()
{
    hEvent_ = ::CreateEvent(NULL, FALSE, FALSE, L"");
}

MessageLoop::~MessageLoop()
{
    if (hEvent_)
        ::CloseHandle(hEvent_);
}

void MessageLoop::AddTask(const CallBack& callback)
{    
    AutoLock lock(lock_); // 如果界面添加任务。工作线程添加任务，工作线程先执行，那可能会卡界面。 应该可以忽略卡界面的情况    
    message_.push(callback);
    ::SetEvent(hEvent_);
}

bool MessageLoop::Loop()
{
    if (PeekTask())
    {
        ResetEvent(hEvent_);
    }
    
    ::WaitForSingleObject(hEvent_, INFINITE);
    CallBack f;
    {
        AutoLock lock(lock_);
        auto f = message_.front();
    }
    if (f)
        f();

    {
        AutoLock lock(lock_);
        message_.pop();
    }
    return true;
}

bool MessageLoop::PeekTask()
{
    AutoLock lock(lock_);
    return message_.empty();
}
