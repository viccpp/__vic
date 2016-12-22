#include<__vic/string_buffer.h>
#include<iostream>
#include<exception>
#include<cassert>

void run_tests()
{
    const size_t intial_capacity = 64;
    __vic::string_buffer s(intial_capacity);
    assert(s.empty());
    assert(s.capacity() >= intial_capacity);

    s << 1;
    assert(s == "1");
    s << ' ' << 2.0 << " " << true;
    std::string std_str = s;
    s = std_str;
    const char *c_str = s;
    s.clear() << static_cast<const void *>(c_str);
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
