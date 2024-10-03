// std::FILE sreader
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2017

#ifndef __VIC_SREADERS_CSTREAM_H
#define __VIC_SREADERS_CSTREAM_H

#include<__vic/stdio_file.h>
#include<cstdio>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
// sreader<char> + sreader<unsigned char>
class cstream_sreader
{
    std::FILE *fp;
public:
    explicit cstream_sreader(std::FILE *fp) : fp(fp) {}
    bool operator()(char &ch) { return __vic::read(fp, ch); }
    bool operator()(unsigned char &ch) { return __vic::read(fp, ch); }
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
