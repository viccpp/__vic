#ifndef __VIC_USE_MODULES
#include<__vic/posix/thread.h>
#include<__vic/posix/sigset.h>
#include<iostream>
#include<exception>
#endif
#include<cassert>
#include<csignal>
#ifdef __VIC_USE_MODULES
import std;
import __vic;
#endif

void run_tests()
{
#if __cpp_initializer_lists
    __vic::posix::sigset set{ SIGINT };
#else
    __vic::posix::sigset set = __vic::posix::sigset::empty() << SIGINT;
#endif
    __vic::posix::this_thread::block_signals(set);
    std::raise(SIGINT);
    std::cout << "Catching SIGINT... " << std::flush;
    int sig = __vic::posix::this_thread::sigwait(set);
    std::cout << "Caught!" << std::endl;
    assert(sig == SIGINT);
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
