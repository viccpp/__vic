#include<__vic/fs.h>
#include<iostream>
#include<exception>
#include<cassert>

void run_tests()
{
    const char * const dir = "mkdir-test";

    __vic::rmdir_if_exists(dir);
    assert(!__vic::path_exists(dir));
    __vic::mkdir(dir);
    assert(__vic::path_exists(dir));
    __vic::rmdir(dir);
    assert(!__vic::path_exists(dir));

    assert(__vic::mkdir_if_absent(dir));
    assert(__vic::path_exists(dir));
    assert(!__vic::mkdir_if_absent(dir));
    assert(__vic::path_exists(dir));
    __vic::rmdir(dir);

    assert(__vic::file_exists("mkdir.cpp"));
    try
    {
        __vic::mkdir_if_absent("mkdir.cpp");
        assert(false);
    }
    catch(const std::exception &ex)
    {
        std::cout << ex.what() << '\n';
    }
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
