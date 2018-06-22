// Types, constants and macros definitions
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2007

#ifndef __VIC_DEFS_H
#define __VIC_DEFS_H

#include<__vic/_cfg.h>
#include<cstddef>
#include<new>
#if __cpp_rvalue_references
#include<utility> // for std::move(), std::forward(), std::swap()
#endif

#if __cplusplus < 201103L && !defined(__VIC_NO_NULLPTR_DEF) && !defined(nullptr)
#ifdef __SUNPRO_CC
#define nullptr 0
#else
const int nullptr = 0;
#endif
#endif

namespace __vic {

using std::size_t;

#if __cplusplus >= 201103L

// Constructor tag to suppress initialization in constructors
class uninitialized {};
constexpr uninitialized noinit{};

//////////////////////////////////////////////////////////////////////////////
// Copy-protection utility. Just inherit this class
//////////////////////////////////////////////////////////////////////////////
class non_copyable
{
public:
    non_copyable(const non_copyable &) = delete;
    non_copyable &operator=(const non_copyable &) = delete;
protected:
    non_copyable() = default;
};
//////////////////////////////////////////////////////////////////////////////
// Inheriting forbids free store allocation for class objects
//////////////////////////////////////////////////////////////////////////////
class non_heap_allocatable
{
public:
    void *operator new(size_t ) = delete;
    void *operator new(size_t , const std::nothrow_t & ) noexcept = delete;
    void *operator new[](size_t ) = delete;
    void *operator new[](size_t , const std::nothrow_t & ) noexcept = delete;
protected:
    non_heap_allocatable() = default;
};
//////////////////////////////////////////////////////////////////////////////

#else // C++98

enum uninitialized { noinit };

//////////////////////////////////////////////////////////////////////////////
class non_copyable
{
    non_copyable(const non_copyable &); // not implemented
    non_copyable &operator=(const non_copyable &); // not implemented
protected:
    non_copyable() {}
};
//////////////////////////////////////////////////////////////////////////////
class non_heap_allocatable
{
    void *operator new(std::size_t ); // not implemented
    void *operator new(std::size_t , const std::nothrow_t & ); // not implemented
    void *operator new[](std::size_t ); // not implemented
    void *operator new[](std::size_t , const std::nothrow_t & ); // not implemented
protected:
    non_heap_allocatable() {}
};
//////////////////////////////////////////////////////////////////////////////

#endif // C++ ver

//----------------------------------------------------------------------------
// Size of the built-in array in elements
template<class T, size_t N>
__VIC_CONSTEXPR_FUNC size_t array_size(T (&)[N])
{
    return N;
}
//----------------------------------------------------------------------------

} // namespace

#endif // header guard
