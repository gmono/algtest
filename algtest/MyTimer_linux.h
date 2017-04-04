#ifndef MYTIMER_LINUX_H
#define MYTIMER_LINUX_H
//linux timer
#include <sys/time.h>
class MyTimer
{
private:
    timeval _freq;
    timeval _start;
    timeval _stop;
public:

    MyTimer()
    {
        gettimeofday(&_freq,nullptr);
    }

    inline void start()
    {
        gettimeofday(&_start,nullptr);
    }

    inline void stop()
    {
        gettimeofday(&_stop,nullptr);
    }


    inline long long ticks()
    {
        return (_stop.tv_sec - _start.tv_sec)*1e6+_stop.tv_usec-_start.tv_usec;
    }
};

#endif // MYTIMER_LINUX_H
