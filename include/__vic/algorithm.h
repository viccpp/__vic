// Generic algorithms
//
// Platform: ISO C++ 98/20
// $Id$
//
// (c) __vic 2021

#ifndef __VIC_ALGORITHM_H
#define __VIC_ALGORITHM_H

#include<__vic/defs.h>
#if __cpp_concepts >= 201907
#include<concepts>
#include<iterator>
#endif

namespace __vic {

//----------------------------------------------------------------------------
#if __cpp_concepts >= 201907
template<
    std::forward_iterator Iter,
    std::predicate<std::iter_value_t<Iter>> Pred
>
#else
template<class Iter, class Pred>
#endif
inline Iter skip_if_front(Iter begin, Iter end, Pred pred)
{
    while(begin != end && pred(*begin)) ++begin;
    return begin;
}
//----------------------------------------------------------------------------
#if __cpp_concepts >= 201907
template<
    std::bidirectional_iterator Iter,
    std::predicate<std::iter_value_t<Iter>> Pred
>
#else
template<class Iter, class Pred>
#endif
inline Iter skip_if_back(Iter begin, Iter end, Pred pred)
{
    while(begin != end)
    {
        Iter last = end; --last;
        if(!pred(*last)) break;
        end = last;
    }
    return end;
}
//----------------------------------------------------------------------------

} // namespace

#endif // header guard
