#include<__vic/bin_file.h>
#include<iostream>
#include<exception>
#include<cstdio>
#include<cassert>

void run_tests()
{
    __vic::bin_file in("bin_file.cpp", __vic::bin_file::in);
    assert(in.is_open());
    __vic::bin_file out("bin_file.copy", __vic::bin_file::out);
    assert(out.is_open());

    char buf[BUFSIZ];
    while(size_t n = in.read_some(buf, sizeof buf))
        out.write_all(buf, n);
    in.close();
    assert(!in.is_open());
    out.close();
    assert(!out.is_open());

    // TODO: assert content of the files is identical

    assert(std::remove("bin_file.copy") == 0);
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
