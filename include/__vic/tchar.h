// Generic algorithms for manipulating null-terminated character sequences
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2008

#ifndef __VIC_TCHAR_H
#define __VIC_TCHAR_H

#include<__vic/defs.h>
#include<string> // for char_traits
#include<cstring>
#include<cwchar>
#if !__cpp_lambdas
#include<functional>
#endif

namespace __vic { namespace tchar {

//----------------------------------------------------------------------------
// String length (generic strlen)
//----------------------------------------------------------------------------
template<class charT>
inline size_t length(const charT *st)
{
    return std::char_traits<charT>::length(st);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Find end of sequence (pointer to null-terminator)
//----------------------------------------------------------------------------
template<class charT>
const charT *end(const charT *st)
{
    while(*st != charT()) st++;
    return st;
}
//----------------------------------------------------------------------------
template<>
inline const char *end(const char *st)
{
    return std::strchr(st, '\x0');
}
//----------------------------------------------------------------------------
template<>
inline const wchar_t *end(const wchar_t *st)
{
    return std::wcschr(st, L'\x0');
}
//----------------------------------------------------------------------------
template<class charT>
inline charT *end(charT *st)
{
    return const_cast<charT*>(end(const_cast<const charT *>(st)));
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Compare strings (generic strcmp, wcscmp)
//----------------------------------------------------------------------------
template<class charT>
inline int compare(const charT *s1, const charT *s2)
{
    for(; *s1 && *s2; ++s1, ++s2)
        if(*s1 != *s2) return *s1 < *s2 ? -1 : 1;
    if(!*s1 &&  *s2) return -1; // s1 < s2
    if( *s1 && !*s2) return  1; // s1 > s2
    return 0; // s1 == s2
}
//----------------------------------------------------------------------------
template<>
inline int compare(const char *s1, const char *s2)
{
    return std::strcmp(s1, s2);
}
//----------------------------------------------------------------------------
template<>
inline int compare(const wchar_t *s1, const wchar_t *s2)
{
    return std::wcscmp(s1, s2);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Copy string (generic strcpy, wcscpy)
//----------------------------------------------------------------------------
template<class charT>
inline charT *copy(charT *dest, const charT *src, size_t n)
{
    std::memcpy(dest, src, n*sizeof(charT));
    return dest;
}
//----------------------------------------------------------------------------
template<class charT>
inline charT *copy(charT *dest, const charT *src)
{
    return copy(dest, src, length(src) + 1);
}
//----------------------------------------------------------------------------
template<>
inline char *copy(char *dest, const char *src)
{
    return std::strcpy(dest, src);
}
//----------------------------------------------------------------------------
template<>
inline wchar_t *copy(wchar_t *dest, const wchar_t *src)
{
    return std::wcscpy(dest, src);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Move the string in memory (generic memmove)
//----------------------------------------------------------------------------
template<class charT>
inline charT *move(charT *dest, const charT *src)
{
    std::memmove(dest, src, (length(src) + 1) * sizeof(charT));
    return dest;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Add a one string to another (generic strcat)
//----------------------------------------------------------------------------
template<class charT>
charT *concat(charT *dest, const charT *src)
{
    return copy(end(dest), src);
}
//----------------------------------------------------------------------------
template<>
inline char *concat(char *dest, const char *src)
{
    return std::strcat(dest, src);
}
//----------------------------------------------------------------------------
template<>
inline wchar_t *concat(wchar_t *dest, const wchar_t *src)
{
    return std::wcscat(dest, src);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Find first character in a string that satisfies a specified condition
//----------------------------------------------------------------------------
template<class charT, class Pred>
const charT *find_if(const charT *st, Pred pred)
{
    for(; *st; st++)
        if(pred(*st)) return st;
    return nullptr;
}
//----------------------------------------------------------------------------
template<class charT, class Pred>
inline charT *find_if(charT *st, Pred pred)
{
    return const_cast<charT*>(find_if(const_cast<const charT *>(st), pred));
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Find first character in a string that not satisfies a specified condition
//----------------------------------------------------------------------------
template<class charT, class Pred>
const charT *find_if_not(const charT *st, Pred pred)
{
    for(; *st; st++)
        if(!pred(*st)) return st;
    return nullptr;
}
//----------------------------------------------------------------------------
template<class charT, class Pred>
inline charT *find_if_not(charT *st, Pred pred)
{
    return const_cast<charT*>(find_if_not(const_cast<const charT *>(st), pred));
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Find last character in a string that satisfies a specified condition
//----------------------------------------------------------------------------
template<class charT, class Pred>
const charT *rfind_if(const charT *st, Pred pred)
{
    for(const charT *p = end(st) - 1; p >= st; p--)
        if(pred(*p)) return p;
    return nullptr;
}
//----------------------------------------------------------------------------
template<class charT, class Pred>
inline charT *rfind_if(charT *st, Pred pred)
{
    return const_cast<charT*>(rfind_if(const_cast<const charT *>(st), pred));
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Find last character in a string that not satisfies a specified condition
//----------------------------------------------------------------------------
template<class charT, class Pred>
const charT *rfind_if_not(const charT *st, Pred pred)
{
    for(const charT *p = end(st) - 1; p >= st; p--)
        if(!pred(*p)) return p;
    return nullptr;
}
//----------------------------------------------------------------------------
template<class charT, class Pred>
inline charT *rfind_if_not(charT *st, Pred pred)
{
    return const_cast<charT*>(rfind_if_not(const_cast<const charT *>(st), pred));
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Find a first occurrence of char in string (generic strchr)
//----------------------------------------------------------------------------
template<class charT>
inline const charT *find(const charT *st, charT ch)
{
    return find_if(st,
#if __cpp_lambdas
        [ch](charT c) { return c == ch; }
#else
        std::bind2nd(std::equal_to<charT>(), ch)
#endif
    );
}
//----------------------------------------------------------------------------
template<>
inline const char *find(const char *st, char ch)
{
    return std::strchr(st,ch);
}
//----------------------------------------------------------------------------
template<>
inline const wchar_t *find(const wchar_t *st, wchar_t ch)
{
    return std::wcschr(st,ch);
}
//----------------------------------------------------------------------------
template<class charT>
inline charT *find(charT *st, charT ch)
{
    return const_cast<charT*>(find(const_cast<const charT *>(st), ch));
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Find a first occurrence of substring in string (generic strstr)
//----------------------------------------------------------------------------
template<class charT>
const charT *find(const charT *st, const charT *sub)
{
    for(; *st; st++)
    {
        if(*st == *sub)
        {
            const charT *p = st, *q = sub;
            while(*p && *q && *p != *q) p++, q++;
            if(*q == charT()) return st;
        }
    }
    return nullptr;
}
//----------------------------------------------------------------------------
template<>
inline const char *find(const char *st, const char *sub)
{
    return std::strstr(st,sub);
}
//----------------------------------------------------------------------------
template<>
inline const wchar_t *find(const wchar_t *st, const wchar_t *sub)
{
    return std::wcsstr(st,sub);
}
//----------------------------------------------------------------------------
template<class charT>
inline charT *find(charT *st, const charT *sub)
{
    return const_cast<charT*>(find(const_cast<const charT *>(st), sub));
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Find a last occurrence of ch in string or NULL (generic strrchr)
//----------------------------------------------------------------------------
template<class charT>
inline const charT *rfind(const charT *st, charT ch)
{
    return rfind_if(st,
#if __cpp_lambdas
        [ch](charT c) { return c == ch; }
#else
        std::bind2nd(std::equal_to<charT>(), ch)
#endif
    );
}
//----------------------------------------------------------------------------
template<>
inline const char *rfind(const char *st, char ch)
{
    return std::strrchr(st,ch);
}
//----------------------------------------------------------------------------
template<>
inline const wchar_t *rfind(const wchar_t *st, wchar_t ch)
{
    return std::wcsrchr(st,ch);
}
//----------------------------------------------------------------------------
template<class charT>
inline charT *rfind(charT *st, charT ch)
{
    return const_cast<charT*>(rfind(const_cast<const charT *>(st), ch));
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Find a first occurrence of any character from
// specified set in string (generic strpbrk)
//----------------------------------------------------------------------------
template<class charT>
const charT *find_first_of(const charT *st, const charT *set)
{
    for(; *st; st++)
        for(const charT *p = set; *p; p++) if(*st == *p) return st;
    return nullptr;
}
//----------------------------------------------------------------------------
template<>
inline const char *find_first_of(const char *st, const char *set)
{
    return std::strpbrk(st, set);
}
//----------------------------------------------------------------------------
template<>
inline const wchar_t *find_first_of(const wchar_t *st, const wchar_t *set)
{
    return std::wcspbrk(st, set);
}
//----------------------------------------------------------------------------
template<class charT>
inline charT *find_first_of(charT *st, const charT *set)
{
    return const_cast<charT*>(find_first_of(const_cast<const charT *>(st), set));
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Find a first character in a string that does NOT belong
// to a set (generic strspn, that returns pointer instead of index)
//----------------------------------------------------------------------------
template<class charT>
const charT *find_first_not_of(const charT *st, const charT *set)
{
    for(; *st; st++)
        for(const charT *p = set; *p; p++) if(*st != *p) return st;
    return nullptr;
}
//----------------------------------------------------------------------------
template<>
inline const char *find_first_not_of(const char *st, const char *set)
{
    return st + std::strspn(st, set);
}
//----------------------------------------------------------------------------
template<>
inline const wchar_t *find_first_not_of(const wchar_t *st, const wchar_t *set)
{
    return st + std::wcsspn(st, set);
}
//----------------------------------------------------------------------------
template<class charT>
inline charT *find_first_not_of(charT *st, const charT *set)
{
    return const_cast<charT*>(find_first_not_of(const_cast<const charT *>(st), set));
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Find a last occurrence of any character from specified set in string
//----------------------------------------------------------------------------
template<class charT>
const charT *find_last_of(const charT *st, const charT *set)
{
    const charT *p = end(st) - 1;
    while(p >= st && !find(set, *p)) p--;
    return p >= st ? p : nullptr;
}
//----------------------------------------------------------------------------
template<class charT>
inline charT *find_last_of(charT *st, const charT *set)
{
    return const_cast<charT*>(find_last_of(const_cast<const charT *>(st), set));
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Find a last character in a string that does NOT belong to a set
//----------------------------------------------------------------------------
template<class charT>
const charT *find_last_not_of(const charT *st, const charT *set)
{
    const charT *p = end(st) - 1;
    while(p >= st && find(set, *p)) p--;
    return p >= st ? p : nullptr;
}
//----------------------------------------------------------------------------
template<class charT>
inline charT *find_last_not_of(charT *st, const charT *set)
{
    return const_cast<charT*>(find_last_not_of(const_cast<const charT *>(st), set));
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Skip all occurrences of the specified character at the begin of the string
//----------------------------------------------------------------------------
template<class charT>
const charT *skip(const charT *p, charT ch)
{
    while(*p && *p == ch) p++;
    return p;
}
//----------------------------------------------------------------------------
template<class charT>
charT *skip(charT *p, charT ch)
{
    return const_cast<charT*>(skip(const_cast<const charT *>(p), ch));
}
//----------------------------------------------------------------------------

}} // namespace

#endif // header guard
