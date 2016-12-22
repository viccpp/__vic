#include<__vic/to_text.h>
#include<iostream>
#include<exception>
#include<cassert>

void run_tests()
{
    std::string st;
    __vic::to_text_append(123, st);
    assert(st == "123");
    __vic::to_text_append(45UL, st);
    assert(st == "12345");
    st.clear();
    __vic::to_text_append(1.2, st);
    __vic::to_text_append(true, st);
    __vic::to_text_append(short(1), st);
    __vic::to_text_append(&st, st);
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
