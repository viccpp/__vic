// std::string reader
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_READERS_STRING_H
#define __VIC_READERS_STRING_H

#include<__vic/readers/container.h>
#include<string>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
template<
    class charT,
    class Tr = std::char_traits<charT>,
    class Al = std::allocator<charT>
>
class basic_string_reader
{
    container_reader<std::basic_string<charT,Tr,Al> > r;
public:
    explicit basic_string_reader(const std::basic_string<charT,Tr,Al> &s)
        : r(s) {}
    bool read(charT &ch) { return r.read(ch); }
};
//////////////////////////////////////////////////////////////////////////////
// Reader<char> + Reader<unsigned char>
template<class Tr, class Al>
class basic_string_reader<char,Tr,Al>
{
    container_reader<std::basic_string<char,Tr,Al> > r;
public:
    explicit basic_string_reader(const std::basic_string<char,Tr,Al> &s)
        : r(s) {}
    bool read(char &ch) { return r.read(ch); }
    bool read(unsigned char &ch) { return read(reinterpret_cast<char&>(ch)); }
};
//////////////////////////////////////////////////////////////////////////////
typedef basic_string_reader<char> string_reader;

} // namespace

#endif // header guard
