#include<__vic/posix/signal.h>
#include<__vic/string_buffer.h>
#include<__vic/throw_errno.h>
#include<signal.h>

namespace __vic { namespace posix {

//----------------------------------------------------------------------------
void ignore_signals(const int sigs[], size_t n)
{
    struct ::sigaction sa;
    sa.sa_handler = SIG_IGN;
    ::sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    for(const int *s = sigs; n--; s++)
        if(::sigaction(*s, &sa, nullptr)) throw_errno(__vic::msg(32) <<
            "Ignoring signo " << *s << " failed");
}
//----------------------------------------------------------------------------

}} // namespace
