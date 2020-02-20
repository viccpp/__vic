// Converters of non-character C++ fundamental types to some text representation
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2007

#ifndef __VIC_TO_TEXT_H
#define __VIC_TO_TEXT_H

#include<__vic/defs.h>
#include<string>

namespace __vic {

void to_text_append(long , std::string & );
void to_text_append(unsigned long , std::string & );

#ifdef __VIC_LONGLONG
void to_text_append(__VIC_LONGLONG , std::string & );
void to_text_append(unsigned __VIC_LONGLONG , std::string & );
#endif

void to_text_append(double , std::string & );
void to_text_append(long double , std::string & );

void to_text_append(const void * , std::string & );

//----------------------------------------------------------------------------
inline void to_text_append(int n, std::string &s)
{
    to_text_append(static_cast<long>(n), s);
}
inline void to_text_append(unsigned n, std::string &s)
{
    to_text_append(static_cast<unsigned long>(n), s);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
inline void to_text_append(short n, std::string &s)
{
    to_text_append(static_cast<long>(n), s);
}
inline void to_text_append(unsigned short n, std::string &s)
{
    to_text_append(static_cast<unsigned long>(n), s);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// [un]signed char is treated as an integer type!!
//----------------------------------------------------------------------------
inline void to_text_append(signed char n, std::string &s)
{
    to_text_append(static_cast<int>(n), s);
}
inline void to_text(unsigned char n, std::string &s)
{
    to_text_append(static_cast<unsigned>(n), s);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
inline void to_text_append(float n, std::string &s)
{
    to_text_append(static_cast<double>(n), s);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
inline void to_text_append(bool f, std::string &s)
{
    s += (f ? '1' : '0');
}
//----------------------------------------------------------------------------

} // namespace

#endif // header guard
