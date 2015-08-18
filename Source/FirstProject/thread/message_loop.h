#ifndef _MESSAGE_LOOP_H_
#define _MESSAGE_LOOP_H_

#include <queue>
#include <functional>

#include "AutoLock.h"
#include "thread_type.h"

// 界面不允许使用 MessageLoop 这样会卡界面。（也许可以忽略）

class MessageLoop
{
public:
    MessageLoop();
    ~MessageLoop();

    void AddTask(const CallBack& callback);

private:
    friend class WinThread;

    bool Loop();
    bool PeekTask();

    std::queue<CallBack> message_;
    CritSect lock_;
    HANDLE hEvent_;
};

#endif