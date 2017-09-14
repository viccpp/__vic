// push_back() wrater
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

} // namespace

#endif // header guard
