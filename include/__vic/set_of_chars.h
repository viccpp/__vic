// Optimized implementation of a set of chars
// Complexity of the contains() operation: constant
// Required space: 32 bytes
//
// Platform: ISO C++ 98/11/14
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_SET_OF_CHARS_H
#define __VIC_SET_OF_CHARS_H

#include<__vic/defs.h>
#include<cstring>
#if __cpp_initializer_lists
#include<initializer_list>
#endif

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
class set_of_chars
{
    unsigned char set[32] // set of 256 bits
#if __cpp_initializer_lists
        = {}
#endif
    ;
public:
#if __cpp_initializer_lists
    __VIC_CONSTEXPR_FUNC set_of_chars() __VIC_DEFAULT_CTR
    template<class Iter>
    __VIC_CONSTEXPR14 set_of_chars(Iter begin, Iter end) { add(begin, end); }
    __VIC_CONSTEXPR14 set_of_chars(const char *c_str) { add(c_str); }
    __VIC_CONSTEXPR14 set_of_chars(std::initializer_list<char> set) { add(set); }
#else
    set_of_chars() { clear(); }
    template<class Iter>
    set_of_chars(Iter begin, Iter end) { assign(begin, end); }
    set_of_chars(const char *c_str) { assign(c_str); }
#endif

    __VIC_CONSTEXPR_FUNC bool contains(char ch) const
    {
        return set[static_cast<unsigned char>(ch) >> 3] & (1 << (ch & 7));
    }

    __VIC_CONSTEXPR14 void add(char ch)
    {
        // Set the corresponding bit
        set[static_cast<unsigned char>(ch) >> 3] |= 1 << (ch & 7);
    }
    __VIC_CONSTEXPR14 void remove(char ch)
    {
        // Reset the corresponding bit
        set[static_cast<unsigned char>(ch) >> 3] &= ~(1 << (ch & 7));
    }

    template<class Iter>
    __VIC_CONSTEXPR14 void add(Iter begin, Iter end)
    {
        while(begin != end) add(*begin++);
    }
    __VIC_CONSTEXPR14 void add(const char *c_str)
    {
        while(*c_str) add(*c_str++);
    }

    template<class Iter>
    void assign(Iter begin, Iter end)
    {
        clear();
        add(begin, end);
    }
    void assign(const char *c_str)
    {
        clear();
        add(c_str);
    }

#if __cpp_initializer_lists
    __VIC_CONSTEXPR14 void add(std::initializer_list<char> set)
    {
        add(set.begin(), set.end());
    }
    void assign(std::initializer_list<char> set)
    {
        clear();
        add(set);
    }
#endif

    void clear() { std::memset(set, 0, sizeof set); }
};
//////////////////////////////////////////////////////////////////////////////

} // namespace

#endif // header guard
