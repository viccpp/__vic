// push_back() writer
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_WRITERS_PUSH_BACK_H
#define __VIC_WRITERS_PUSH_BACK_H

#include<__vic/defs.h>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
template<class Cont, class T = typename Cont::value_type>
class push_back_writer
{
    Cont *cont;
public:
    explicit push_back_writer(Cont &c) : cont(&c) {}
    void write(T v) { cont->push_back(v); }
};
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
template<class Cont>
inline push_back_writer<Cont> make_push_back_writer(Cont &c)
{
    return push_back_writer<Cont>(c);
}
//----------------------------------------------------------------------------
template<class T, class Cont>
inline push_back_writer<Cont,T> make_push_back_writer_for(Cont &c)
{
    return push_back_writer<Cont,T>(c);
}
//----------------------------------------------------------------------------

} // namespace

#endif // header guard
