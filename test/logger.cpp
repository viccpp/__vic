#include<__vic/logger.h>
#include<iostream>
#include<exception>

//////////////////////////////////////////////////////////////////////////////
class clogger : public __vic::logger
{
public:
    explicit clogger(message_severity level = severity::info)
        : logger(level) {}
protected:
    void publish_record(message_severity s, const char *rec, size_t rec_len)
    {
        (std::clog << to_string(s) << ": ").write(rec, rec_len) << std::endl;
    }
};
//////////////////////////////////////////////////////////////////////////////

void run_tests()
{
    clogger log(clogger::severity::debug);

    log.info() << "Application is started";

    for(int i = 0; i < 5; i++)
        log.debug() << "Loop i = " << i;

    // Explicit log record construction
    {
        clogger::record rec = log.warning();
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
