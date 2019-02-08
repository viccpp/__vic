#include<__vic/tchar.h>
#include<iostream>
#include<exception>
#include<cassert>
#include<cctype>

namespace tests {

namespace tchar = __vic::tchar;

struct is_upper
{
    bool operator()(char c) const { return std::isupper(c); }
};

void run()
{
    assert(tchar::length("abc") == 3);
    assert(tchar::length(L"abc") == 3);

    assert(*tchar::end("abc") == '\x0');

    assert(tchar::compare("ab", "ab") == 0);
    assert(tchar::compare("ab", "ac") < 0);
    assert(tchar::compare("ab", "aa") > 0);
    assert(tchar::compare("a", "ab") < 0);

    char st[32] = "a";
    tchar::concat(st, "b");
    assert(tchar::equal(st, "ab"));

    const char *p;
    p = tchar::find("abc", 'b');
    assert(p && *p == 'b');

    p = tchar::find("abcd", "cd");
    assert(p && *p == 'c');

    p = tchar::find_if("abCd", is_upper());
    assert(p && *p == 'C');

    p = tchar::find_first_of("abcd", "bc");
    assert(p && *p == 'b');

    p = tchar::find_last_of("abcd", "bc");
    assert(p && *p == 'c');

    p = tchar::find_first_not_of("abcd", "ab");
    assert(p && *p == 'c');

    p = tchar::find_last_not_of("abcda", "ab");
    assert(p && *p == 'd');

    assert(*tchar::skip("    ab", ' ') == 'a');
    assert(*tchar::skip("ab", ' ') == 'a');
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
