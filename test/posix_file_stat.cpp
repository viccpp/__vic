#include<__vic/posix/file_stat.h>
#include<iostream>
#include<exception>
#include<cassert>

void run_tests()
{
    __vic::posix::file_stat s;

    assert(s.try_get("posix_file_stat.cpp") == true);
    s.get("posix_file_stat.cpp");
    assert(s.is_regular());

    assert(s.try_get("posix_file_stat.notexists") == false);

    struct ::stat ss = s;
    s = ss;
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
