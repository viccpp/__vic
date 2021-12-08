// Internal header. Functional objects (predicates) on char
//
// Platform: ISO C++ 98
// $Id$
//
// (c) __vic 2021

#ifndef __VIC_CHAR_PREDICATES_H
#define __VIC_CHAR_PREDICATES_H

#include<__vic/ascii.h>
#include<__vic/set_of_chars.h>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
struct is_ascii_ws
{
    bool operator()(char ch) const { return ascii::isspace(ch); }
};
//////////////////////////////////////////////////////////////////////////////
class is_eq_char
{
    char c;
public:
    explicit is_eq_char(char ch) : c(ch) {}
    bool operator()(char ch) const { return ch == c; }
};
//////////////////////////////////////////////////////////////////////////////
class is_one_of_chars
{
    set_of_chars set;
public:
    explicit is_one_of_chars(const char *chars) : set(chars) {}
    bool operator()(char ch) const { return set.contains(ch); }
};
//////////////////////////////////////////////////////////////////////////////

} // namespace

#endif // header guard
