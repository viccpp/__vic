// Filesystem utilities
//
// Platform: ISO C++ 98/11 - POSIX
// $Id$
//
// (c) __vic 2012

#ifndef __VIC_POSIX_FS_H
#define __VIC_POSIX_FS_H

#include<string>

namespace __vic { namespace posix {

//----------------------------------------------------------------------------
std::string dirname(const std::string & );
std::string basename(const std::string & );
void dirname(const std::string & , std::string & );
void basename(const std::string & , std::string & );
void append_dirname(const std::string & , std::string & );
void append_basename(const std::string & , std::string & );
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
inline std::string &add_trailing_slash(std::string &s)
{
    if(!s.empty() && *s.rbegin() != '/') s += '/';
    return s;
}
inline std::string with_trailing_slash(std::string s)
{
    return add_trailing_slash(s);
}
inline std::string with_trailing_slash(const char *s)
{
    return with_trailing_slash(s ? std::string(s) : std::string());
}
//----------------------------------------------------------------------------

}} // namespace

#endif // header guard
