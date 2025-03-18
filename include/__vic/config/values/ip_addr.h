// Value parser for __vic::ipv4_addr
//
// Platform: ISO C++ 98
// $Id$
//
// (c) __vic 2019

#ifndef __VIC_CONFIG_VALUES_IP_ADDR_H
#define __VIC_CONFIG_VALUES_IP_ADDR_H

#include<__vic/config/value.h>
#include<__vic/ip_addr.h>

namespace __vic { namespace config {

//////////////////////////////////////////////////////////////////////////////
template<> struct value<ipv4_addr>
{
    static bool parse(const std::string &s, ipv4_addr &res)
    {
        return ipv4_addr::parse(s, res);
    }
};
//////////////////////////////////////////////////////////////////////////////

}} // namespace

#endif // header guard
