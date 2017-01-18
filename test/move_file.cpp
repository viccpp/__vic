#include<__vic/fs.h>
#include<iostream>
#include<exception>
#include<cassert>

void run_tests()
{
    assert(!__vic::path_exists("not-existing-file"));
    __vic::remove_file_if_exists("move.res");
    assert(!__vic::path_exists("move.res"));
    bool res = __vic::move_file_if_exists("not-existing-file", "move.res");
    assert(!res);

    __vic::remove_file_if_exists("copy.res");
    assert(!__vic::path_exists("copy.res"));
    __vic::copy_file("move_file.cpp", "copy.res");
    assert(__vic::file_exists("copy.res"));
    res = __vic::move_file_if_exists("copy.res", "move.res");
    assert(res);
    assert(!__vic::file_exists("copy.res"));
    assert(__vic::file_exists("move.res"));

    __vic::remove_file_if_exists("rename.res");
    assert(!__vic::file_exists("rename.res"));
    __vic::rename_file("move.res", "rename.res");
    assert(!__vic::file_exists("move.res"));
    assert(__vic::file_exists("rename.res"));

    __vic::remove_file("rename.res");
    assert(!__vic::path_exists("rename.res"));
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
