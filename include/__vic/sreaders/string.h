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
template<class charT>
struct basic_string_sreader : public iterator_sreader_n<const charT *>
{
    template<class Tr, class Al>
    explicit basic_string_sreader(const std::basic_string<charT,Tr,Al> &s)
        : iterator_sreader_n<const charT *>(s.data(), s.length()) {}
};
//////////////////////////////////////////////////////////////////////////////
// sreader<char> + sreader<unsigned char>
template<>
class basic_string_sreader<char>
{
    iterator_sreader_n<const char *> r;
public:
    template<class Tr, class Al>
    explicit basic_string_sreader(const std::basic_string<char,Tr,Al> &s)
        : r(s.data(), s.length()) {}
    bool operator()(char &ch) { return r(ch); }
    bool operator()(unsigned char &ch) { return (*this)(reinterpret_cast<char&>(ch)); }
    const char *position() const { return r.position(); }
};
//////////////////////////////////////////////////////////////////////////////
typedef basic_string_sreader<char> string_sreader;

//----------------------------------------------------------------------------
template<class charT, class Tr, class Al>
inline basic_string_sreader<charT>
    make_string_sreader(const std::basic_string<charT,Tr,Al> &s)
{
    return basic_string_sreader<charT>(s);
}
//----------------------------------------------------------------------------

} // namespace

#endif // header guard
