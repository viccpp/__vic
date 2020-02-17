#include<__vic/posix/iov.h>
#include<__vic/defs.h>
#include<iostream>
#include<exception>
#include<cstring>
#include<cassert>

namespace tests {

template<unsigned N>
inline void add_str(__vic::posix::ovectors<N> &v, const char *st)
{
    v.push_back(st, std::strlen(st));
}
void ovectors_test()
{
    __vic::posix::ovectors<3> v;
    add_str(v, "ovectors");
    add_str(v, " works!");
    const char nl = '\n';
    v.push_back(&nl, 1);
    __vic::posix::writev_all(1, v);
}
void run()
{
    // test 1
    ::iovec v[3];

    v[0].iov_base = nullptr;
    v[0].iov_len = 2;

    v[1].iov_base = nullptr;
    v[1].iov_len = 4;

    v[2].iov_base = nullptr;
    v[2].iov_len = 8;

    assert(__vic::posix::total(v) == 2 + 4 + 8);

    // test 2
    ::iovec *p = v;
    unsigned v_len = __vic::array_size(v);
    __vic::posix::cut_prefix(p, v_len, 8);

    assert(v_len == 1);
    assert(p == &v[2]);
    assert(__vic::posix::total(p, v_len) == 6);

    // test 3
    v[0].iov_len = 2;
    v[1].iov_len = 4;
    v[2].iov_len = 8;

    p = v;
    v_len = __vic::array_size(v);
    __vic::posix::cut_prefix(p, v_len, 100);
    assert(v_len == 0);

    ovectors_test();
}

} // namespace

int main()
{
    try
    {
        tests::run();
        return 0;
    }
    catch(const std::exception &ex)
    {
        std::cerr << ex.what() << '\n';
    }
    return 1;
}
