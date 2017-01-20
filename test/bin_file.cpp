#include<__vic/bin_file.h>
#include<iostream>
#include<exception>
#include<cstdio>
#include<cassert>

void copy_test()
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
void throw_if_closed_test()
{
    __vic::bin_file file("file_doesnt_exist", __vic::bin_file::in);
    if(!file.is_open()) file.open_in("bin_file.cpp");
    file.throw_if_closed("Cannot open file");
}
void throw_last_error_test()
{
    __vic::bin_file file;
    if(!file.open_in("bin_file.cpp"))
        file.throw_last_error("Cannot open file");
}
void run_tests()
{
    copy_test();
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
