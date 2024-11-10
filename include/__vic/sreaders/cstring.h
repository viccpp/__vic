// NULL-terminated C-string sreader
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_SREADERS_CSTRING_H
#define __VIC_SREADERS_CSTRING_H

#include<__vic/defs.h>
#include<__vic/sreaders/result.h>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
template<class charT>
class basic_cstring_sreader
{
    const charT *st;
public:
    explicit basic_cstring_sreader(const charT *s) : st(s) {}
    sread_result<charT> operator()()
    {
        if(charT b = *st)
        {
            st++;
            return b;
        }
        return sread_eof;
    }
    const charT *position() const { return st; }
};
//////////////////////////////////////////////////////////////////////////////
typedef basic_cstring_sreader<char> cstring_sreader;

//----------------------------------------------------------------------------
template<class charT>
inline basic_cstring_sreader<charT> make_cstring_sreader(const charT *s)
{
    return basic_cstring_sreader<charT>(s);
}
//----------------------------------------------------------------------------

} // namespace

#endif // header guard
