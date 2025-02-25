//
// $Id$
//

#include<__vic/ip_addr.h>
#include<__vic/windows/throw_last_error.h>
#include<ws2tcpip.h>

namespace __vic {

//----------------------------------------------------------------------------
void to_text_append(const ::in6_addr &ip, std::string &s)
{
    char st[64]; // INET6_ADDRSTRLEN == 46
    if(!inet_ntop(AF_INET6, &ip, st, sizeof st))
        windows::throw_wsa_error("inet_ntop(AF_INET6)");
    s += st;
}
//----------------------------------------------------------------------------

} // namespace
