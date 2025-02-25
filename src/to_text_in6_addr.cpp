//
// $Id$
//

#include<__vic/ip_addr.h>
#include<__vic/throw_errno.h>
#include<arpa/inet.h>

namespace __vic {

//----------------------------------------------------------------------------
void to_text_append(const ::in6_addr &ip, std::string &s)
{
    char st[64]; // INET6_ADDRSTRLEN == 46
    if(!inet_ntop(AF_INET6, &ip, st, sizeof st))
        throw_errno("inet_ntop(AF_INET6)");
    s += st;
}
//----------------------------------------------------------------------------

} // namespace
