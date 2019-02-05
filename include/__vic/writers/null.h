// null writer
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2018

#ifndef __VIC_WRITERS_NULL_H
#define __VIC_WRITERS_NULL_H

#include<__vic/defs.h>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
struct null_writer
{
    template<class T> void write(T ) {}
};
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
inline null_writer make_null_writer()
{
    return null_writer();
}
//----------------------------------------------------------------------------

} // namespace

#endif // header guard
