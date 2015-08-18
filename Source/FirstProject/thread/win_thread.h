#ifndef _WIN_THREAD_H_
#define _WIN_THREAD_H_

#include <string>
#include <memory>
#include <Windows.h>

#include "thread_type.h"

class MessageLoop;

class WinThread
{
public:
    explicit WinThread(const std::string& thread_name);
    virtual ~WinThread();

    unsigned int GetThreadId() const { return thread_id_; }
    
    void AddTask(const CallBack& callback);

    bool isRunning() const { return isrunning_; }
    void Start();
    void Stop();

    void SetPriority(T_PRIORITY priority);
    T_PRIORITY GetPriority() const { priority_; }

    std::wstring GetThreadName() const { name_; }

    HANDLE GetThreadHandle() { return handle_; }    
protected:
    virtual void Run();

    std::unique_ptr<MessageLoop> messgae_loop;

private:
    static unsigned int __stdcall ThreadMain(void* thread);
    DWORD SuspendThread();
    DWORD ResumeThread();

    struct THREADNAME_INFO
    {
        DWORD dwType;
        LPCSTR szName;
        DWORD dwThreadID;
        DWORD dwFlags;
    };
    void SetThreadName();

    HANDLE handle_;
    std::string name_;
    T_PRIORITY priority_;
    unsigned int thread_id_;
    bool isrunning_;
};
#endif