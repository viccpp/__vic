//
// $Id$
//

#include<__vic/posix/iov.h>
#include<cassert>

namespace __vic { namespace posix {

//----------------------------------------------------------------------------
void cut_prefix(::iovec *&vec, unsigned &vec_len, size_t n)
{
    ::iovec *v = vec;
    unsigned len = vec_len;

    for(; len != 0 && v->iov_len <= n; len--)
    {
        n -= v->iov_len;
        v++;
    }
    if(len == 0 || v->iov_len <= n)
    {
        vec_len = 0;
        return; // n >= total(vec, vec_len)
    }
    assert(len > 0 && v->iov_len > n);
    if(n != 0)
    {
        v->iov_base = static_cast<char *>(v->iov_base) + n;
        v->iov_len -= n;
    }

    vec = v;
    vec_len = len;
}
//----------------------------------------------------------------------------

}} // namespace
