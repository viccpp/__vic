// Vectored I/O utils
//
// Platform: ISO C++ 98/11 - POSIX
// $Id$
//
// (c) __vic 2012

#ifndef __VIC_POSIX_IOV_H
#define __VIC_POSIX_IOV_H

#include<__vic/defs.h>
#include<sys/uio.h>
#include<limits.h> // for IOV_MAX
#include<cassert>

namespace __vic { namespace posix {

//////////////////////////////////////////////////////////////////////////////
template<unsigned N>
class ovectors
{
    ::iovec v[N], *next_;
    size_t total_;
#if __cpp_static_assert
    static_assert(N <= IOV_MAX, "ovector cannot be greater than IOV_MAX");
#else
    typedef char assert_size_is_not_too_big[N <= IOV_MAX ? 1 : -1];
#endif
public:
    ovectors() : next_(v), total_(0) {}

    void push_back(const void *p, size_t n)
    {
        assert(size() < max_size());
        next_->iov_base = const_cast<void *>(p);
        next_->iov_len  = n;
        next_++;
        total_ += n;
    }
    void pop_back()
    {
        assert(!empty());
        next_--;
        total_ -= next_->iov_len;
    }

    ::iovec *ptr() { return v; }
    const ::iovec *ptr() const { return v; }
    unsigned size() const { return next_ - v; }

    bool full() const { return next_ == v + N; }
    bool empty() const { return next_ == v; }
    void clear() { next_ = v; total_ = 0; }

    static __VIC_CONSTEXPR_FUNC unsigned max_size() { return N; }
    size_t total_bytes() const { return total_; }
};
//////////////////////////////////////////////////////////////////////////////
// TODO: class ivectors

//----------------------------------------------------------------------------
inline size_t total(const ::iovec *v, unsigned v_len)
{
    size_t res = 0;
    for(; v_len--; v++) res += v->iov_len;
    return res;
}
//----------------------------------------------------------------------------
template<unsigned vsize>
inline size_t total(const ::iovec (&v)[vsize])
{
    return total(v, vsize);
}
//----------------------------------------------------------------------------

void cut_prefix(::iovec *& , unsigned & , size_t );

void writev_all(int , ::iovec * , unsigned , size_t );
//----------------------------------------------------------------------------
template<unsigned vsize>
inline void writev_all(int fd, ovectors<vsize> &v)
{
    writev_all(fd, v.ptr(), v.size(), v.total_bytes());
}
//----------------------------------------------------------------------------

}} // namespace

#endif // header guard
