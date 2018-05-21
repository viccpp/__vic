// The pool controlling objects lifetime
// Objects are not required be CopyConstructable
// Pool is organized as stack
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2007

#ifndef __VIC_OBJECT_POOL_H
#define __VIC_OBJECT_POOL_H

#include<__vic/defs.h>
#include<new>
#include<exception>
#include __VIC_SWAP_HEADER

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
// Internal class. Use object_pool<T>::overflow
struct object_pool_overflow_ : public std::exception
{
    const char *what() const noexcept { return "__vic::object_pool: Overflow"; }
};
//////////////////////////////////////////////////////////////////////////////
template<class T>
class object_pool : private non_copyable
{
    T *pool, *next, *limit;

    static T *allocate(size_t n)
        { return static_cast<T *>(::operator new[](sizeof(T) * n)); }
    static void deallocate(T *p) { ::operator delete[](p); }
    static void destroy(T *p) { p->~T(); }
public:
    typedef T object_type;
    typedef object_type value_type; // standard synonym
    typedef object_type *iterator;
    typedef const object_type *const_iterator;
    typedef object_pool_overflow_ overflow;

    object_pool() : pool(0), next(0), limit(0) {}
    explicit object_pool(size_t );
    ~object_pool();

#if __cpp_rvalue_references
    object_pool(object_pool &&o) noexcept
        : pool(o.pool), next(o.next), limit(o.limit)
    {
        o.pool = o.next = o.limit = nullptr;
    }
    object_pool &operator=(object_pool &&o) noexcept { swap(o); return *this; }
#if __cpp_variadic_templates
    template<class... Args> T &emplace(Args &&... );
#endif
#endif

    // size in objects
    size_t size() const { return next - pool; }
    size_t capacity() const { return limit - pool; }
    bool full() const { return next == limit; }
    bool empty() const { return next == pool; }

    void recreate(size_t , bool = false);
    void pop()
    {
        if(next != pool) destroy(--next);
    }
    void clear()
    {
        // destruct all objects
        while(next != pool) destroy(--next);
    }
    void swap(object_pool &o) noexcept
    {
        std::swap(pool, o.pool);
        std::swap(next, o.next);
        std::swap(limit, o.limit);
    }
    // BEGIN: Deprecated functions. Use emplace() in C++11 mode
    // returns pointer to memory for object allocation
    void *alloc()
    {
        if(full()) throw overflow();
        return next;
    }
    // adds last allocated object to the pool
    void push() { next++; }
    // END: Deprecated functions

    // element access
    object_type &operator[](size_t i) { return pool[i]; }
    iterator begin() { return pool; }
    iterator end() { return next; }
    object_type &front() { return *pool; }
    object_type &back() { return *(next-1); }

    const object_type &operator[](size_t i) const { return pool[i]; }
    const_iterator begin() const { return pool; }
    const_iterator end() const { return next; }
    const_iterator cbegin() const { return begin(); }
    const_iterator cend() const { return end(); }
    const object_type &front() const { return *pool; }
    const object_type &back() const { return *(next-1); }
};
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
template<class T>
object_pool<T>::object_pool(size_t max_size)
{
    pool = next = this->allocate(max_size);
    limit = pool + max_size;
}
//----------------------------------------------------------------------------
template<class T>
object_pool<T>::~object_pool()
{
    clear();
    deallocate(pool);
}
//----------------------------------------------------------------------------
template<class T>
void object_pool<T>::recreate(size_t max_size, bool exact)
{
    clear();
    if(max_size > capacity() || (exact && max_size != capacity()))
    {
        deallocate(pool);
        pool = next = this->allocate(max_size);
        limit = pool + max_size;
    }
}
//----------------------------------------------------------------------------
#if __cpp_rvalue_references && __cpp_variadic_templates
template<class T>
template<class... Args>
T &object_pool<T>::emplace(Args &&... args)
{
    if(full()) throw overflow();
    T *obj = ::new(static_cast<void*>(next))
        object_type(std::forward<Args>(args)...);
    next++;
    return *obj;
}
#endif
//----------------------------------------------------------------------------
template<class T>
inline void swap(object_pool<T> &o1, object_pool<T> &o2) noexcept { o1.swap(o2); }
//----------------------------------------------------------------------------

} // namespace

#endif // header guard
