// std::string swriter
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_SWRITERS_STRING_H
#define __VIC_SWRITERS_STRING_H

#include<__vic/swriters/push_back.h>
#include<string>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
template<
    class charT,
    class Tr = std::char_traits<charT>,
    class Al = std::allocator<charT>
>
struct basic_string_swriter :
    public push_back_swriter<std::basic_string<charT,Tr,Al> >
{
    explicit basic_string_swriter(std::basic_string<charT,Tr,Al> &s)
        : push_back_swriter<std::basic_string<charT,Tr,Al> >(s) {}
};
//////////////////////////////////////////////////////////////////////////////
typedef basic_string_swriter<char> string_swriter;

//----------------------------------------------------------------------------
template<class charT, class Tr, class Al>
inline basic_string_swriter<charT,Tr,Al>
    make_string_swriter(std::basic_string<charT,Tr,Al> &s)
{
    return basic_string_swriter<charT,Tr,Al>(s);
}
//----------------------------------------------------------------------------

} // namespace

#endif // header guard
