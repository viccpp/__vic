#include<__vic/waitable_event.h>
#include<__vic/thread.h>
#include<iostream>
#include<exception>
#include<cstring>

namespace tests {

//////////////////////////////////////////////////////////////////////////////
class worker_thread : public __vic::thread
{
    __vic::waitable_event stop_work;
    void worker();
public:
    void stop() { stop_work.set(); }
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
    __vic::this_thread::sleep_ms(200);
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
        stop_work.wait_ms(1000);
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
