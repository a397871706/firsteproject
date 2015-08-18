#include "stdafx.h"
#include "AutoLock.h"


AutoLock::AutoLock(CritSect& c)
    :cs_(c)
{
    cs_.Acquire();
}

AutoLock::~AutoLock()
{
    cs_.Release();
}
