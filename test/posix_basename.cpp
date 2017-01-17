#include<__vic/posix/fs.h>
#include<iostream>
#include<exception>
#include<cassert>

// WARNING: no brackets around macro arguments
#define test_basename(src, expected_res) \
{ \
    std::string res = __vic::posix::basename(src); \
    std::cout << "basename " << (*src ? src : "\"\"") << " -> " \
        << (res.empty() ? "\"\"" : res.c_str()) << std::endl; \
    assert(__vic::posix::basename(src) == expected_res); \
\
    __vic::posix::basename(src, res); \
    std::cout << "basename (out) " << (*src ? src : "\"\"") << " -> " \
        << (res.empty() ? "\"\"" : res.c_str()) << std::endl; \
    assert(res == expected_res); \
\
    res = ">>>"; \
    __vic::posix::append_basename(src, res); \
    std::cout << "append_basename " << (*src ? src : "\"\"") << " -> " \
        << res << std::endl; \
    assert(res == std::string(">>>") + expected_res); \
}
#define test_dirname(src, expected_res) \
{ \
    std::string res = __vic::posix::dirname(src); \
    std::cout << "dirname " << (*src ? src : "\"\"") << " -> " \
        << (res.empty() ? "\"\"" : res.c_str()) << std::endl; \
    assert(__vic::posix::dirname(src) == expected_res); \
\
    __vic::posix::dirname(src, res); \
    std::cout << "dirname (out) " << (*src ? src : "\"\"") << " -> " \
        << (res.empty() ? "\"\"" : res.c_str()) << std::endl; \
    assert(res == expected_res); \
\
    res = ">>>"; \
    __vic::posix::append_dirname(src, res); \
    std::cout << "append_dirname " << (*src ? src : "\"\"") << " -> " \
        << res << std::endl; \
    assert(res == std::string(">>>") + expected_res); \
}
void dirname_tests()
{
    test_dirname("", ".");
    test_dirname("/usr/lib", "/usr");
    test_dirname("/usr/", "/");
    test_dirname("usr", ".");
    test_dirname("/", "/");
    test_dirname("..", ".");
}
void basename_tests()
{
    test_basename("", "");
    test_basename("/usr/lib", "lib");
    test_basename("/usr/lib/", "lib");
    test_basename("usr", "usr");
    test_basename("/", "/");
    test_basename("..", "..");
}
void run_tests()
{
    dirname_tests();
    basename_tests();
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
