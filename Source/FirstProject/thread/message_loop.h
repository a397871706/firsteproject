#ifndef _MESSAGE_LOOP_H_
#define _MESSAGE_LOOP_H_

#include <queue>
#include <functional>

#include "AutoLock.h"
#include "thread_type.h"

// ���治����ʹ�� MessageLoop �����Ῠ���档��Ҳ����Ժ��ԣ�

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