// std::FILE sreader
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2017

#ifndef __VIC_SREADERS_CSTREAM_H
#define __VIC_SREADERS_CSTREAM_H

#include<__vic/sreaders/result.h>
#include<__vic/stdio_file.h>
#include<cstdio>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
class cstream_sreader
{
    std::FILE *fp;
public:
    explicit cstream_sreader(std::FILE *fp) : fp(fp) {}
    sread_result<char> operator()() { return __vic::read(fp); }
};
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
inline cstream_sreader make_cstream_sreader(std::FILE *fp)
{
    return cstream_sreader(fp);
}
//----------------------------------------------------------------------------

} // namespace

#endif // header guard
