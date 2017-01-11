#include<__vic/posix/time.h>
#include<iostream>
#include<exception>
#include<cassert>
#include<ctime>

void run_tests()
{
    __vic::posix::time_spec t = __vic::posix::nanoseconds_since_epoch();
    char st[64];
    std::strftime(st, sizeof st,
        "%H:%M:%S %d.%m.%Y", std::localtime(&t.tv_sec));
    std::cout << "Current time: " << st << '\n';
#if _POSIX_TIMERS > 0
    t = __vic::posix::realtime_clock::get_time();
    std::strftime(st, sizeof st,
        "%H:%M:%S %d.%m.%Y", std::localtime(&t.tv_sec));
    std::cout << "Current (real) time: " << st << '\n';
#ifdef _POSIX_MONOTONIC_CLOCK
    std::cout << "Monotonic elapsed: " <<
        __vic::posix::monotonic_clock::get_time().tv_sec << " seconds \n";
#endif
#ifdef __VIC_HAVE_STD_CHRONO
    std::cout << "Nanoseconds since 1970: " <<
        __vic::posix::realtime_clock::now().time_since_epoch().count() << '\n';
#endif
#endif
}

int main()
{
    try
    {
        run_tests();
        return 0;
    }
    catch(const std::exception &ex)
    {
        std::cerr << ex.what() << '\n';
    }
    return 1;
}
