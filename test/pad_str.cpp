#include<__vic/string_utils.h>
#include<iostream>
#include<exception>
#include<cstring>
#include<cassert>

namespace tests {

void cstring_test()
{
    char st[10];

    std::strcpy(st, "1");
    std::cout << st << " -> "; std::cout << __vic::pad_front(st, 4, '0') << std::endl;
    assert(std::strcmp(st, "0001") == 0);
    __vic::pad_front(st, 4, '0');
    assert(std::strcmp(st, "0001") == 0);

    std::strcpy(st, "1");
    std::cout << st << " -> "; std::cout << __vic::pad_back(st, 4, '0') << std::endl;
    assert(std::strcmp(st, "1000") == 0);
    __vic::pad_back(st, 4, '0');
    assert(std::strcmp(st, "1000") == 0);
}
void string_test()
{
    std::string st;

    st = "1";
    std::cout << st << " -> "; std::cout << __vic::pad_front(st, 4, '0') << std::endl;
    assert(st == "0001");
    __vic::pad_front(st, 4, '0');
    assert(st == "0001");

    st = "1";
    std::cout << st << " -> "; std::cout << __vic::pad_back(st, 4, '0') << std::endl;
    assert(st == "1000");
    __vic::pad_back(st, 4, '0');
    assert(st == "1000");
}
void run()
{
    cstring_test();
    string_test();
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
