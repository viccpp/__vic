#include<__vic/posix/signal.h>
#include<__vic/posix/thread.h>
#include<iostream>
#include<exception>
#include<cassert>

void run_tests()
{
#if __cpp_initializer_lists
    __vic::posix::sigset set{ SIGINT };
#else
    __vic::posix::sigset set = __vic::posix::sigset::empty() << SIGINT;
#endif
    __vic::posix::this_thread::block_signals(set);
    std::cout << "*** PRESS Ctrl+C ***" << std::endl;
    __vic::posix::this_thread::sigwait(set);
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
