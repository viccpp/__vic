// null swriter
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2018

#ifndef __VIC_SWRITERS_NULL_H
#define __VIC_SWRITERS_NULL_H

#include<__vic/defs.h>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
struct null_swriter
{
    template<class T> void write(T ) {}
};
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
inline null_swriter make_null_swriter()
{
    return null_swriter();
}
//----------------------------------------------------------------------------

} // namespace

#endif // header guard
