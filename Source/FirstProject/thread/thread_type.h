#ifndef _THREAD_TYPE_H_
#define _THREAD_TYPE_H_
#include <functional>


namespace
{
typedef std::function<void(void)>  CallBack;


enum T_PRIORITY
{
    LOWEST = -2,
    BELOW = -1,
    NORMAL = 0,
    ABOVE = 1,
    HIGHEST = 2,
    CRITICAL = 15,
};

}
#endif