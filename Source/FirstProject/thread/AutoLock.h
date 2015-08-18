#ifndef _AUTOLOCK_H_
#define _AUTOLOCK_H_

#include <Windows.h>

class AutoLock;

class CritSect
{
public:
    CritSect() { ::InitializeCriticalSection(&cs_); }
    ~CritSect() { ::DeleteCriticalSection(&cs_); }

private:
    friend class AutoLock;
    void Acquire() { ::EnterCriticalSection(&cs_); }
    void Release() { ::LeaveCriticalSection(&cs_); }

    CRITICAL_SECTION cs_;
};

class AutoLock
{
public:
    explicit AutoLock(CritSect& c);
    ~AutoLock();

private:
    AutoLock(const AutoLock& l);
    void operator=(const AutoLock& l);

    CritSect& cs_;    
    //DISALLOW_COPY_AND_ASSIGN(AutoLock);
};

#endif