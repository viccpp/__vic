// ASCII-strings processing tools
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2017

#ifndef __VIC_ASCII_STRING_H
#define __VIC_ASCII_STRING_H

#include<__vic/defs.h>
#include<string>

namespace __vic { namespace ascii {

//----------------------------------------------------------------------------
char *toupper(char * );
char *tolower(char * );
std::string &toupper(std::string & );
std::string &tolower(std::string & );
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
bool equal_icase(const char * , const char * );
bool equal_icase(const char * , size_t , const char * , size_t );

inline bool equal_icase(const std::string &s1, const std::string &s2)
{
    return equal_icase(s1.data(), s1.length(), s2.data(), s2.length());
}
inline bool equal_icase(const std::string &s1, const char *s2)
{
    return equal_icase(s1.c_str(), s2);
}
inline bool equal_icase(const char *s1, const std::string &s2)
{
    return equal_icase(s1, s2.c_str());
}
//----------------------------------------------------------------------------

}} // namespace

#endif // header guard
