#include<__vic/logger.h>
#include<iostream>
#include<exception>

//////////////////////////////////////////////////////////////////////////////
class coutput : public __vic::logger::output
{
public:
    void publish_record(__vic::logger::severity_t s,
                            const char *rec, size_t rec_len)
    {
        (std::clog << to_string(s) << ": ").write(rec, rec_len) << std::endl;
    }
};
//////////////////////////////////////////////////////////////////////////////

void run_tests()
{
    coutput log_output;
    __vic::logger log(log_output, __vic::logger::severity::debug);

    log.info() << "Application is started";

    for(int i = 0; i < 5; i++)
        log.debug() << "Loop i = " << i;

    // Explicit log record construction
    {
        __vic::logger::record rec = log.warning();
        rec << "a ";
        rec << "b ";
        rec << "c";
    }

    log.warning("Application end");
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
