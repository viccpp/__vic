#include<__vic/algorithm.h>
#include<__vic/tchar.h>
#include<iostream>
#include<exception>
#include<cassert>

namespace tests {

//////////////////////////////////////////////////////////////////////////////
class is_eq_char
{
    char c;
public:
    explicit is_eq_char(char ch) : c(ch) {}
    bool operator()(char ch) const { return ch == c; }
};
//////////////////////////////////////////////////////////////////////////////

void skip_if_tests()
{
    const char src[] = "..abc...";
    const char * const end = __vic::tchar::end(src);

    const char *b = __vic::skip_if_front(src, end, is_eq_char('.'));
    assert(*b == 'a');

    const char *e = __vic::skip_if_back(src, end, is_eq_char('.'));
    assert(e > src);
    assert(*(e - 1) == 'c');
}
void run()
{
    skip_if_tests();
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
