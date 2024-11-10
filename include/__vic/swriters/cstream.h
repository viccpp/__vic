// std::FILE swriter
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2017

#ifndef __VIC_SWRITERS_CSTREAM_H
#define __VIC_SWRITERS_CSTREAM_H

#include<__vic/stdio_file.h>
#include<cstdio>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
// swriter<char>
class cstream_swriter
{
    std::FILE *fp;
public:
    explicit cstream_swriter(std::FILE *fp) : fp(fp) {}
    void operator()(char ch) { __vic::write(fp, ch); }
};
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
inline cstream_swriter make_cstream_swriter(std::FILE *fp)
{
    return cstream_swriter(fp);
}
//----------------------------------------------------------------------------

} // namespace

#endif // header guard
