//
// $Id$
//

#include<__vic/error.h>
#include<cstring>
#if defined __linux__ || defined __FreeBSD__ || defined __sun || defined _AIX
#include<string.h> // for strerror_r
#include<cstdio>
#define __VIC_USE_STRERROR_R 1
#endif

namespace __vic {

#ifdef __VIC_USE_STRERROR_R
namespace {
//----------------------------------------------------------------------------
// Redirector to POSIX-variant
inline const char *call(int (*strerror_r)(int, char *, size_t),
                                int errnum, char *buf, size_t buflen)
{
    if(strerror_r(errnum, buf, buflen))
    {
        std::sprintf(buf, "strerror_r: <Couldn't get message for %d>", errnum);
    }
    buf[buflen - 1] = '\x0';
    return buf;
}
//----------------------------------------------------------------------------
// Redirector to GNU-variant
inline const char *call(char *(*strerror_r)(int, char *, size_t),
                                int errnum, char *buf, size_t buflen)
{
    return strerror_r(errnum, buf, buflen);
}
//----------------------------------------------------------------------------
} // namespace
#endif // __VIC_USE_STRERROR_R

//----------------------------------------------------------------------------
libc_error::libc_error(int no)
    : code_(no), formatted(false)
{
}
//----------------------------------------------------------------------------
libc_error::libc_error(const char *prompt, int no)
    : code_(no), formatted(false), msg(prompt)
{
}
//----------------------------------------------------------------------------
const char *libc_error::what() const noexcept
{
    try
    {
        if(!formatted)
        {
            const char *err_msg;
#ifdef __VIC_USE_STRERROR_R
            char err_msg_buf[256];
            err_msg = call(strerror_r, code(), err_msg_buf, sizeof err_msg_buf);
#else // Windows, HP-UX, etc...
            err_msg = std::strerror(code());
#endif

            if(msg.empty()) msg = err_msg;
            else // prompt: err_msg
            {
                size_t msg_len = std::strlen(msg);
                size_t err_msg_len = std::strlen(err_msg);
                readonly_cstring tmp;
                char *p = tmp.reserve(msg_len + err_msg_len + 3); // 3 is ": " + '\0'
                std::memcpy(p, msg, msg_len);
                p += msg_len;
                *p++ = ':';
                *p++ = ' ';
                std::memcpy(p, err_msg, err_msg_len + 1); // with '\0'
                msg.swap(tmp);
            }
            formatted = true;
        }
        return msg;
    }
    catch(...)
    {
        return "libc_error::what(): <Couldn't format error message>";
    }
}
//----------------------------------------------------------------------------

} // namespace
