// std::string sreader
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_SREADERS_STRING_H
#define __VIC_SREADERS_STRING_H

#include<__vic/sreaders/iterator.h>
#include<string>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
template<
    class charT,
    class Tr = std::char_traits<charT>,
    class Al = std::allocator<charT>
>
class basic_string_sreader
{
    iterator_sreader_n<const charT *> r;
public:
    explicit basic_string_sreader(const std::basic_string<charT,Tr,Al> &s)
        : r(s.data(), s.length()) {}
    bool read(charT &ch) { return r.read(ch); }
    const charT *position() const { return r.position(); }
};
//////////////////////////////////////////////////////////////////////////////
// sreader<char> + sreader<unsigned char>
template<class Tr, class Al>
class basic_string_sreader<char,Tr,Al>
{
    iterator_sreader_n<const char *> r;
public:
    explicit basic_string_sreader(const std::basic_string<char,Tr,Al> &s)
        : r(s.data(), s.length()) {}
    bool read(char &ch) { return r.read(ch); }
    bool read(unsigned char &ch) { return read(reinterpret_cast<char&>(ch)); }
    const char *position() const { return r.position(); }
};
//////////////////////////////////////////////////////////////////////////////
typedef basic_string_sreader<char> string_sreader;

//----------------------------------------------------------------------------
template<class charT, class Tr, class Al>
inline basic_string_sreader<charT,Tr,Al>
    make_string_sreader(const std::basic_string<charT,Tr,Al> &s)
{
    return basic_string_sreader<charT,Tr,Al>(s);
}
//----------------------------------------------------------------------------

} // namespace

#endif // header guard
