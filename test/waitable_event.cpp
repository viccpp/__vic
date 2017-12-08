#include<iostream>
#include<exception>
#include<cstring>

#if __cplusplus >= 201103L // C++11
#include<__vic/waitable_event.h>
#include<thread>

namespace tests {

//////////////////////////////////////////////////////////////////////////////
class worker_thread
{
    __vic::waitable_event stop_work;
    std::thread t;
    void worker();
public:
    void start() { t = std::thread{[this]{ worker(); }}; }
    void stop() { stop_work.set(); }
    void join() { t.join(); }
};
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
bool have_job()
{
    static int counter = 0;
    if(counter++ > 10)
    {
        counter = 0;
        return false;
    }
    return true;
}
//----------------------------------------------------------------------------
void process_one_item()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}
//----------------------------------------------------------------------------
void worker_thread::worker()
{
    while(!stop_work.signaled())
    {
        while(have_job())
        {
            process_one_item();
            if(stop_work.signaled()) return;
        }
        stop_work.wait_for(std::chrono::seconds(1));
    }
}
//----------------------------------------------------------------------------
void run()
{
    worker_thread thr;
    thr.start();

    std::cout << "*** PRESS ENTER TO TERMINATE THREAD ***" << std::endl;
    std::cin.get();

    thr.stop();
    thr.join();
    std::cout << "Done" << std::endl;
}
//----------------------------------------------------------------------------

} // namespace
#else // C++98
namespace tests { void run() {} }
#endif

int main(int argc, char *argv[])
{
    try
    {
        if(argc == 2 && std::strcmp(argv[1], "interactive") == 0)
            tests::run();
        return 0;
    }
    catch(const std::exception &ex)
    {
        std::cerr << ex.what() << '\n';
    }
    return 1;
}
