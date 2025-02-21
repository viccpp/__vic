#include<__vic/ip_addr.h>
#include<iostream>
#include<exception>
#include<cassert>

void run_ipv4_tests()
{
    using __vic::ipv4_addr;
    ipv4_addr ip;
    assert(ipv4_addr::parse("127.0.0.1", ip));
    assert(ip == ipv4_addr(127,0,0,1));

    assert(ipv4_addr::parse("255.255.255.255", ip));
    assert(ip == ipv4_addr(255,255,255,255));

    assert(!ipv4_addr::parse("", ip));
    assert(!ipv4_addr::parse("127", ip));
    assert(!ipv4_addr::parse("256.0.0.1", ip));

    assert(ipv4_addr(0,0,0,0).is_any());
    assert(ipv4_addr::any().is_any());
    assert(ipv4_addr(127,0,0,1).is_loopback());
    assert(ipv4_addr::loopback().is_loopback());
    assert((ipv4_addr(10,1,2,3) & ipv4_addr(255,0,0,0)) == ipv4_addr(10,0,0,0));

    std::string st;
    to_text_append(ipv4_addr(1,2,3,4), st);
    assert(st == "1.2.3.4");
}
void run_ipv6_tests()
{
    using __vic::ipv4_addr;
    using __vic::ipv6_addr;
    ipv6_addr ip;

    assert(ipv6_addr::parse(
        "0102:0304:0506:0708:090A:0B0C:0D0E:0F10", ip));
    assert(ip == ipv6_addr(0x0102,0x0304,0x0506,0x0708,
                           0x090A,0x0B0C,0x0D0E,0x0F10));

    assert(ipv6_addr::parse("::1", ip));
    assert(ip == ipv6_addr(0,0,0,0,0,0,0,1));
    assert(ipv6_addr::parse("a00::f", ip));
    assert(ip == ipv6_addr(0xa00,0,0,0,0,0,0,0xf));
    assert(ipv6_addr::parse("1::", ip));
    assert(ip == ipv6_addr(1,0,0,0,0,0,0,0));
    assert(ipv6_addr::parse("::", ip));
    assert(ip == ipv6_addr(0,0,0,0,0,0,0,0));
    assert(ipv6_addr::parse("2001:db8::ab:12", ip));
    assert(ip == ipv6_addr(0x2001,0xdb8,0,0,0,0,0xab,0x12));

    assert(!ipv6_addr::parse("", ip));
    assert(!ipv6_addr::parse("!", ip));
    assert(!ipv6_addr::parse("0G::", ip));
    assert(!ipv6_addr::parse("12345::", ip));
    assert(!ipv6_addr::parse("1:2:3:4:5:6:7", ip));
    assert(!ipv6_addr::parse("1:2:3:4:5:6:7:8:9", ip));
    assert(!ipv6_addr::parse("1:2:3:4:5:6:7::8", ip));
    assert(!ipv6_addr::parse("::1:2:3:4:5:6:7:8", ip));
    assert(!ipv6_addr::parse("1:2:3:4:5:6:7:8::", ip));
    assert(!ipv6_addr::parse("1::2::3", ip));
    // These cases are accepted by inet_pton() in Linux (disallowed by std)
    assert(!ipv6_addr::parse("1:2:3:4:5:6:7::", ip));
    assert(!ipv6_addr::parse("::1:2:3:4:5:6:7", ip));
    assert(!ipv6_addr::parse("1:2:3::4:5:6:7", ip));

    assert(ipv6_addr(0,0,0,0,0,0,0,0).is_any());
    assert(ipv6_addr::any().is_any());
    assert(ipv6_addr(0,0,0,0,0,0,0,1).is_loopback());
    assert(ipv6_addr::loopback().is_loopback());
    assert((ipv6_addr(1,2,3,4,5,6,7,8) &
           ipv6_addr(255,255,255,255,0,0,0,0)) == ipv6_addr(1,2,3,4,0,0,0,0));

    ipv4_addr ip4(1,2,3,4);
    ipv6_addr ipv4_mapped(0,0,0,0,0,0,0,0,0,0,0xff,0xff, 1,2,3,4);
    assert(ipv4_mapped == ipv6_addr(ip4));
    assert(ipv4_mapped.is_ipv4_mapped());
    assert(ipv4_mapped.to_ipv4() == ip4);

    std::string st;
    to_text_append(ipv6_addr(    1,0x203,0x405,0x607,
                             0x809,0xa0b,0xc0d,0xe0f), st);
    assert(st == "1:203:405:607:809:a0b:c0d:e0f");
}

int main()
{
    try
    {
        run_ipv4_tests();
        run_ipv6_tests();
        return 0;
    }
    catch(const std::exception &ex)
    {
        std::cerr << ex.what() << '\n';
    }
    return 1;
}
