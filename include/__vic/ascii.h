// Fast, compact and locale-independent tools for ASCII-characters processing
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2016

#ifndef __VIC_ASCII_H
#define __VIC_ASCII_H

#include<__vic/defs.h>

// FreeBSD 10 defines this
#ifdef isascii
#undef isascii
#endif

namespace __vic { namespace ascii {

//----------------------------------------------------------------------------
__VIC_CONSTEXPR_FUNC bool isdigit(char c)
{
    return '0' <= c && c <= '9';
}
//----------------------------------------------------------------------------
__VIC_CONSTEXPR_FUNC bool isxdigit(char c)
{
    return isdigit(c) || ('A' <= c && c <= 'F') || ('a' <= c && c <= 'f');
}
//----------------------------------------------------------------------------
__VIC_CONSTEXPR_FUNC bool islower(char c)
{
    return 'a' <= c && c <= 'z';
}
//----------------------------------------------------------------------------
__VIC_CONSTEXPR_FUNC bool isupper(char c)
{
    return 'A' <= c && c <= 'Z';
}
//----------------------------------------------------------------------------
__VIC_CONSTEXPR_FUNC bool isalpha(char c)
{
    return islower(c) || isupper(c);
}
//----------------------------------------------------------------------------
__VIC_CONSTEXPR_FUNC bool isalnum(char c)
{
    return isalpha(c) || isdigit(c);
}
//----------------------------------------------------------------------------
__VIC_CONSTEXPR_FUNC bool isspace(char c)
{
    return c == ' ' || ('\t' <= c && c <= '\r');
}
//----------------------------------------------------------------------------
__VIC_CONSTEXPR_FUNC bool isblank(char c)
{
    return c == ' ' || c == '\t';
}
//----------------------------------------------------------------------------
__VIC_CONSTEXPR_FUNC bool isprint(char c)
{
    return ' ' <= c && c <= '~'; // isgraph(c) || c == ' '
}
//----------------------------------------------------------------------------
__VIC_CONSTEXPR_FUNC bool isgraph(char c)
{
    return '!' <= c && c <= '~';
}
//----------------------------------------------------------------------------
__VIC_CONSTEXPR_FUNC bool ispunct(char c)
{
    return ('!' <= c && c <= '/') ||
           (':' <= c && c <= '@') ||
           ('[' <= c && c <= '`') ||
           ('{' <= c && c <= '~') ;
}
//----------------------------------------------------------------------------
__VIC_CONSTEXPR_FUNC bool iscntrl(char c)
{
    return (0 <= c && c <= '\x1F') || c == '\x7F';
}
//----------------------------------------------------------------------------
__VIC_CONSTEXPR_FUNC bool isascii(char c)
{
    return static_cast<unsigned char>(c) < 0x7FU;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
__VIC_CONSTEXPR_FUNC char todigit(int n)
{
    // assert(0 <= n && n <= 9);
    return n + '0';
}
//----------------------------------------------------------------------------
// Convert digit to integer number
// Returns -1 if !isdigit(ch)
__VIC_CONSTEXPR_FUNC int digit_to_number(char ch)
{
    return '0' <= ch && ch <= '9' ? ch - '0' : -1;
}
//----------------------------------------------------------------------------
__VIC_CONSTEXPR_FUNC char toxdigit_upper(int n)
{
    // assert(0 <= n && n <= 15);
    return n < 10 ? n + '0' : n - 10 + 'A';
}
//----------------------------------------------------------------------------
__VIC_CONSTEXPR_FUNC char toxdigit_lower(int n)
{
    // assert(0 <= n && n <= 15);
    return n < 10 ? n + '0' : n - 10 + 'a';
}
//----------------------------------------------------------------------------
// Convert HEX-digit to integer number
// Returns -1 if !isxdigit(ch)
__VIC_CONSTEXPR_FUNC int xdigit_to_number(char ch)
{
    return '0' <= ch && ch <= '9' ? ch - '0' :
           'A' <= ch && ch <= 'F' ? ch - 'A' + 10 :
           'a' <= ch && ch <= 'f' ? ch - 'a' + 10 :
           -1; // Not a hex digit
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Precondition: isupper(upper)
__VIC_CONSTEXPR_FUNC char upper_to_lower(char upper)
{
    // Set the 5-th bit
    return upper | (1 << 5); // or: upper - ('a' - 'A')
}
//----------------------------------------------------------------------------
// Precondition: islower(lower)
__VIC_CONSTEXPR_FUNC char lower_to_upper(char lower)
{
    // Clear the 5-th bit
    return lower & ~(1 << 5); // or: lower + ('a' - 'A')
}
//----------------------------------------------------------------------------
__VIC_CONSTEXPR_FUNC char tolower(char c)
{
    return isupper(c) ? upper_to_lower(c) : c;
}
//----------------------------------------------------------------------------
__VIC_CONSTEXPR_FUNC char toupper(char c)
{
    return islower(c) ? lower_to_upper(c) : c;
}
//----------------------------------------------------------------------------
__VIC_CONSTEXPR_FUNC bool equal_icase(char ch1, char ch2)
{
    return tolower(ch1) == tolower(ch2);
}
//----------------------------------------------------------------------------

}} // namespace

#endif // header guard
