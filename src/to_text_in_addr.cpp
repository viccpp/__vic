//
// $Id$
//

#include<__vic/ip_addr.h>
#include<__vic/to_text.h>

namespace __vic {

//----------------------------------------------------------------------------
void to_text_append(::in_addr ip, std::string &s)
{
    const uint8_t *p = reinterpret_cast<const uint8_t *>(&ip.s_addr);
    to_text_append(p[0], s);
    s += '.';
    to_text_append(p[1], s);
    s += '.';
    to_text_append(p[2], s);
    s += '.';
    to_text_append(p[3], s);
}
//----------------------------------------------------------------------------

} // namespace
