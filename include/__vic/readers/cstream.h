// std::FILE reader
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2017

#ifndef __VIC_READERS_CSTREAM_H
#define __VIC_READERS_CSTREAM_H

#include<__vic/stdio_file.h>
#include<cstdio>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
// Reader<char> + Reader<unsigned char>
class cstream_reader
{
    std::FILE *fp;
public:
    explicit cstream_reader(std::FILE *fp) : fp(fp) {}
    bool read(char &ch) { return __vic::read(fp, ch); }
    bool read(unsigned char &ch) { return __vic::read(fp, ch); }
};
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
inline cstream_reader make_cstream_reader(std::FILE *fp)
{
    return cstream_reader(fp);
}
//----------------------------------------------------------------------------

} // namespace

#endif // header guard
