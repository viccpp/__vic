// Reference to the range of chars
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2009

#ifndef __VIC_STRING_REF_H
#define __VIC_STRING_REF_H

#include<__vic/defs.h>
#include<__vic/tchar.h>
#include<string>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
template<class charT>
class basic_string_ref
{
    const charT *begin_, *end_;
public:
    typedef charT value_type;
    typedef const value_type *iterator;
    typedef iterator const_iterator;

    // Constructors
    __VIC_CONSTEXPR_FUNC basic_string_ref() : begin_(nullptr), end_(nullptr) {}
    basic_string_ref(const charT *st)
        : begin_(st), end_(tchar::end(st)) {}
    basic_string_ref(const charT *st, size_t n)
        : begin_(st), end_(st + n) {}
    basic_string_ref(const charT *b, const charT *e)
        : begin_(b), end_(e) {}
    template<class Traits, class Alloc>
    basic_string_ref(const std::basic_string<charT,Traits,Alloc> &st)
        : begin_(&*st.begin()), end_(&*st.end()) {}
    basic_string_ref(
        typename std::basic_string<charT>::const_iterator begin,
        typename std::basic_string<charT>::const_iterator end
    ) : begin_(&*begin), end_(&*end) {}
#if __cpp_initializer_lists
    basic_string_ref(std::initializer_list<charT> il)
        : begin_(&*il.begin()), end_(&*il.end()) {}
#endif

    // Accessors
    iterator begin() const { return begin_; }
    iterator end() const { return end_; }
    iterator cbegin() const { return begin(); }
    iterator cend() const { return end(); }

    charT front() const { return *begin(); }
    charT back() const { return *(end() - 1); }
    charT operator[](size_t i) const { return begin_[i]; }
    const charT *data() const { return begin_; }

    bool empty() const { return begin() == end(); }
    size_t size() const { return end() - begin(); }
    size_t length() const { return size(); }

    int compare(basic_string_ref ) const;

    // Converters
    std::basic_string<charT>
        str() const { return std::basic_string<charT>(begin(), end()); }
    template<class Traits>
    std::basic_string<charT,Traits>
        str() const { return std::basic_string<charT,Traits>(begin(), end()); }
    template<class Traits, class Alloc>
    std::basic_string<charT,Traits,Alloc> str(const Alloc &a = Alloc()) const
        { return std::basic_string<charT,Traits,Alloc>(begin(), end(), a); }
    operator std::basic_string<charT>() const { return str(); }
};
//////////////////////////////////////////////////////////////////////////////
typedef basic_string_ref<char> string_ref;

//----------------------------------------------------------------------------
template<class charT>
int basic_string_ref<charT>::compare(basic_string_ref<charT> s) const
{
    iterator p = begin(), q = s.begin();
    for(;; ++p, ++q)
    {
        if(p == end()) return q == s.end() ? 0 : -1; // s1 < s2
        if(q == s.end()) return 1; // s1 > s2
        if(*p < *q) return -1; // s1 < s2
        if(*p > *q) return  1; // s1 > s2
    }
}
//----------------------------------------------------------------------------
template<class charT>
inline bool operator==(basic_string_ref<charT> s1, basic_string_ref<charT> s2)
    { return s1.length() == s2.length() && s1.compare(s2) == 0; }
//----------------------------------------------------------------------------
template<class charT>
inline bool operator!=(basic_string_ref<charT> s1, basic_string_ref<charT> s2)
    { return !(s1 == s2); }
//----------------------------------------------------------------------------
template<class charT>
inline bool operator<(basic_string_ref<charT> s1, basic_string_ref<charT> s2)
    { return s1.compare(s2) < 0; }
//----------------------------------------------------------------------------
template<class charT>
inline bool operator>(basic_string_ref<charT> s1, basic_string_ref<charT> s2)
    { return s1.compare(s2) > 0; }
//----------------------------------------------------------------------------
template<class charT>
inline bool operator<=(basic_string_ref<charT> s1, basic_string_ref<charT> s2)
    { return s1.compare(s2) <= 0; }
//----------------------------------------------------------------------------
template<class charT>
inline bool operator>=(basic_string_ref<charT> s1, basic_string_ref<charT> s2)
    { return s1.compare(s2) >= 0; }
//----------------------------------------------------------------------------
// Non-templated operators to force implicit conversions to string_ref
inline bool operator==(string_ref s1, string_ref s2) { return operator== <>(s1, s2); }
inline bool operator!=(string_ref s1, string_ref s2) { return operator!= <>(s1, s2); }
inline bool operator< (string_ref s1, string_ref s2) { return operator<  <>(s1, s2); }
inline bool operator> (string_ref s1, string_ref s2) { return operator>  <>(s1, s2); }
inline bool operator<=(string_ref s1, string_ref s2) { return operator<= <>(s1, s2); }
inline bool operator>=(string_ref s1, string_ref s2) { return operator>= <>(s1, s2); }
//----------------------------------------------------------------------------

} // namespace

#ifdef __VIC_DEFINE_OSTREAM_INSERTERS
#include<ostream>
//----------------------------------------------------------------------------
template<class charT, class Traits>
inline std::basic_ostream<charT,Traits> &operator<<(
    std::basic_ostream<charT,Traits> &os,
    __vic::basic_string_ref<charT> sr)
{
    return os.write(sr.begin(), sr.size());
}
//----------------------------------------------------------------------------
inline std::ostream &operator<<(std::ostream &os, __vic::string_ref sr)
{
    return operator<< <>(os, sr);
}
//----------------------------------------------------------------------------
#endif

#endif // header guard
