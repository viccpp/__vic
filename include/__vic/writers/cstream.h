// std::FILE writer
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2017

#ifndef __VIC_WRITERS_CSTREAM_H
#define __VIC_WRITERS_CSTREAM_H

#include<__vic/stdio_file.h>
#include<cstdio>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
// Writer<char>
class cstream_writer
{
    std::FILE *fp;
public:
    explicit cstream_writer(std::FILE *fp) : fp(fp) {}
    void write(char ch) { __vic::write(fp, ch); }
};
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
inline cstream_writer make_cstream_writer(std::FILE *fp)
{
    return cstream_writer(fp);
}
//----------------------------------------------------------------------------

} // namespace

#endif // header guard
