// push_back() swriter
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_SWRITERS_PUSH_BACK_H
#define __VIC_SWRITERS_PUSH_BACK_H

#include<__vic/defs.h>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
template<class Cont, class T = typename Cont::value_type>
class push_back_swriter
{
    Cont *cont;
public:
    explicit push_back_swriter(Cont &c) : cont(&c) {}
    void operator()(T v) { cont->push_back(v); }
};
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
template<class Cont>
inline push_back_swriter<Cont> make_push_back_swriter(Cont &c)
{
    return push_back_swriter<Cont>(c);
}
//----------------------------------------------------------------------------
template<class T, class Cont>
inline push_back_swriter<Cont,T> make_push_back_swriter_for(Cont &c)
{
    return push_back_swriter<Cont,T>(c);
}
//----------------------------------------------------------------------------

} // namespace

#endif // header guard
