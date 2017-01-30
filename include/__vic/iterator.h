// Iterators-related utilities
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2014

#ifndef __VIC_ITERATOR_H
#define __VIC_ITERATOR_H

#include<__vic/defs.h>
#include<iterator>

namespace __vic {

//------------------------------------------------------------------------------
template<class T, size_t N>
__VIC_CONSTEXPR_FUNC T *begin(T (&arr)[N]) { return arr; }
//------------------------------------------------------------------------------
template<class T, size_t N>
__VIC_CONSTEXPR_FUNC T *end(T (&arr)[N]) { return arr + N; }
//------------------------------------------------------------------------------
template<class T, size_t N>
__VIC_CONSTEXPR_FUNC const T *cbegin(T (&arr)[N]) { return arr; }
//------------------------------------------------------------------------------
template<class T, size_t N>
__VIC_CONSTEXPR_FUNC const T *cend(T (&arr)[N]) { return arr + N; }
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Moves only forward as opposed to std::advance() and never steps beyond the end
// advance(it, end, n) effects as while(it != end && n--) ++it;
//------------------------------------------------------------------------------
template<class Iter>
inline void advance_(std::random_access_iterator_tag, Iter &begin, Iter end, size_t n)
{
    size_t total = end - begin;
    begin += n < total ? n : total;
}
//------------------------------------------------------------------------------
template<class Iter>
inline void advance_(std::input_iterator_tag, Iter &begin, Iter end, size_t n)
{
    Iter it = begin;
    while(it != end && n--) ++it;
    begin = it;
}
//------------------------------------------------------------------------------
template<class Iter>
inline void advance(Iter &begin, Iter end, size_t n)
{
    advance_(typename std::iterator_traits<Iter>::iterator_category(),
        begin, end, n);
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
template<class Iter>
inline Iter next_(std::forward_iterator_tag, Iter it, size_t n)
{
    while(n--) ++it;
    return it;
}
//------------------------------------------------------------------------------
template<class Iter>
inline Iter next_(std::random_access_iterator_tag, Iter it, size_t n)
{
    return it += n;
}
//------------------------------------------------------------------------------
template<class ForwardIterator>
inline ForwardIterator next(ForwardIterator it, size_t n)
{
    return next_(typename std::iterator_traits<ForwardIterator>
        ::iterator_category(), it, n);
}
//------------------------------------------------------------------------------
template<class ForwardIterator>
inline ForwardIterator next(ForwardIterator it)
{
    return ++it;
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
template<class Iter>
inline Iter prev_(std::bidirectional_iterator_tag, Iter it, size_t n)
{
    while(n--) --it;
    return it;
}
//------------------------------------------------------------------------------
template<class Iter>
inline Iter prev_(std::random_access_iterator_tag, Iter it, size_t n)
{
    return it -= n;
}
//------------------------------------------------------------------------------
template<class BidirectionalIterator>
inline BidirectionalIterator prev(BidirectionalIterator it, size_t n)
{
    return prev_(typename std::iterator_traits<BidirectionalIterator>
        ::iterator_category(), it, n);
}
//------------------------------------------------------------------------------
template<class BidirectionalIterator>
inline BidirectionalIterator prev(BidirectionalIterator it)
{
    return --it;
}
//------------------------------------------------------------------------------

} // namespace

#endif // header guard
