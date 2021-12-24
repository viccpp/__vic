//
// $Id$
//

#include<__vic/windows/throw_last_error.h>
#include<__vic/error.h>
#include<cstring>
#include<string>

namespace __vic { namespace windows {

//----------------------------------------------------------------------------
void throw_failed(const char *who)
{
    size_t who_len = std::strlen(who);
    std::string msg;
    msg.reserve(who_len + 7);
    msg.append(who, who_len);
    msg.append(" failed", 7);
    throw exception(msg.c_str());
}
//----------------------------------------------------------------------------

}} // namespace
