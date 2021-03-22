// A vector without autogrowing capacity(). Can hold non-copyable/movable objects
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2007

#ifndef __VIC_FIXED_VECTOR_H
#define __VIC_FIXED_VECTOR_H

#include<__vic/defs.h>
#include<new>
#include __VIC_SWAP_HEADER

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
template<class T>
class fixed_vector : private non_copyable
{
    T *mem, *next, *limit;

    static T *allocate(size_t n)
        { return static_cast<T *>(::operator new[](sizeof(T) * n)); }
    static void deallocate(T *p) { ::operator delete[](p); }
    static void destroy(T *p) { p->~T(); }
public:
    typedef T value_type;
    typedef value_type *iterator;
    typedef const value_type *const_iterator;

    fixed_vector() : mem(0), next(0), limit(0) {}
    explicit fixed_vector(size_t );
    ~fixed_vector();

#if __cpp_rvalue_references
    fixed_vector(fixed_vector &&o) noexcept
        : mem(o.mem), next(o.next), limit(o.limit)
    {
        o.mem = o.next = o.limit = nullptr;
    }
    fixed_vector &operator=(fixed_vector &&o) noexcept { swap(o); return *this; }
#if __cpp_variadic_templates
    template<class... Args> T &emplace_back(Args &&... );
#endif
#endif

    // size in objects
    size_t size() const { return next - mem; }
    size_t capacity() const { return limit - mem; }
    bool full() const { return next == limit; }
    bool empty() const { return next == mem; }

    void recreate(size_t , bool = false);
    void pop_back() { destroy(--next); }
    void clear()
    {
        // destruct all objects
        while(next != mem) destroy(--next);
    }
    void swap(fixed_vector &o) noexcept
    {
        std::swap(mem, o.mem);
        std::swap(next, o.next);
        std::swap(limit, o.limit);
    }
    // BEGIN: Deprecated functions. Use emplace() in C++11 mode
    // returns pointer to memory for object allocation
    void *alloc() { return next; }
    // adds last allocated object to the container
    void push_allocated() { next++; }
    // END: Deprecated functions

    // element access
    T &operator[](size_t i) { return mem[i]; }
    iterator begin() { return mem; }
    iterator end() { return next; }
    T &front() { return *mem; }
    T &back() { return *(next-1); }

    const T &operator[](size_t i) const { return mem[i]; }
    const_iterator begin() const { return mem; }
    const_iterator end() const { return next; }
    const_iterator cbegin() const { return begin(); }
    const_iterator cend() const { return end(); }
    const T &front() const { return *mem; }
    const T &back() const { return *(next-1); }
};
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
template<class T>
fixed_vector<T>::fixed_vector(size_t max_size)
{
    mem = next = this->allocate(max_size);
    limit = mem + max_size;
}
//----------------------------------------------------------------------------
template<class T>
fixed_vector<T>::~fixed_vector()
{
    clear();
    deallocate(mem);
}
//----------------------------------------------------------------------------
template<class T>
void fixed_vector<T>::recreate(size_t max_size, bool exact)
{
    clear();
    if(max_size > capacity() || (exact && max_size != capacity()))
    {
        deallocate(mem);
        mem = next = this->allocate(max_size);
        limit = mem + max_size;
    }
}
//----------------------------------------------------------------------------
#if __cpp_rvalue_references && __cpp_variadic_templates
template<class T>
template<class... Args>
T &fixed_vector<T>::emplace_back(Args &&... args)
{
    T *obj = ::new(static_cast<void*>(next)) T(std::forward<Args>(args)...);
    next++;
    return *obj;
}
#endif
//----------------------------------------------------------------------------
template<class T>
inline void swap(fixed_vector<T> &o1, fixed_vector<T> &o2) noexcept { o1.swap(o2); }
//----------------------------------------------------------------------------

} // namespace

#endif // header guard
