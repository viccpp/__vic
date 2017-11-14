// std::string writer
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_WRITERS_STRING_H
#define __VIC_WRITERS_STRING_H

#include<__vic/writers/push_back.h>
#include<string>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
template<
    class charT,
    class Tr = std::char_traits<charT>,
    class Al = std::allocator<charT>
>
struct basic_string_writer :
    public push_back_writer<std::basic_string<charT,Tr,Al> >
{
    explicit basic_string_writer(std::basic_string<charT,Tr,Al> &s)
        : push_back_writer<std::basic_string<charT,Tr,Al> >(s) {}
};
//////////////////////////////////////////////////////////////////////////////
typedef basic_string_writer<char> string_writer;

} // namespace

#endif // header guard
