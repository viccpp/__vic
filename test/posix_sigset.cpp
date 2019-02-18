#include<__vic/posix/sigset.h>
#include<iostream>
#include<exception>
#include<cassert>

void run_tests()
{
    using __vic::posix::sigset;

    sigset set = sigset::empty();
    assert(!set.is_member(SIGTERM));
    set += SIGTERM;
    assert(set.is_member(SIGTERM));
    set -= SIGTERM;
    assert(!set.is_member(SIGTERM));

    assert(!set.is_member(SIGINT));
    set << SIGINT >> SIGINT;
    assert(!set.is_member(SIGINT));

    int sigs[] = { SIGINT, SIGTERM };
    sigset set2(sigs);
    assert(set2.is_member(SIGINT));
    assert(set2.is_member(SIGTERM));
    set2 = sigs;
    assert(set2.is_member(SIGINT));
    assert(set2.is_member(SIGTERM));
}

int main()
{
    try
    {
        run_tests();
        return 0;
    }
    catch(const std::exception &ex)
    {
        std::cerr << ex.what() << '\n';
    }
    return 1;
}
