#include<__vic/trim.h>
#include<cassert>
#include<iostream>
#include<exception>
#include<cstring>
#include<cctype>

namespace tests {

using namespace __vic;

char last(const char *st)
{
    assert(st && *st != '\0');
    return *(std::strchr(st, '\0') - 1);
}
char last(const std::string &st)
{
    assert(!st.empty());
    return *(st.end() - 1);
}
/*char last(const string_ref &st)
{
    assert(!st.empty());
    return *(st.end() - 1);
}*/
bool not_in_set(char ch, const char *set)
{
    assert(set);
    return !std::strchr(set, ch);
}
// Test internal utilities
void test_utils()
{
    assert(last("123") == '3');
    assert(last(std::string("123")) == '3');
    //assert(last(string_ref("123")) == '3');
    assert(not_in_set('z', "abc"));
    assert(!not_in_set('a', "abc") && !not_in_set('b', "abc") && !not_in_set('c', "abc"));
}

void trim_default_test(const char *src)
{
    assert(src);
    std::cout << "Default trim. Source: |" << src << "|\n";

    char st[32];
    assert(std::strlen(src) < sizeof st);

    std::strcpy(st, src);
    std::cout << trim(st) << "|\n";
    assert(!std::isspace(*st) && !std::isspace(last(st)));

    std::strcpy(st, src);
    std::cout << trim_left(st) << "|\n";
    assert(!std::isspace(*st));

    std::strcpy(st, src);
    std::cout << trim_right(st) << "|\n";
    assert(!std::isspace(last(st)));

    std::string sst;

    sst = src;
    std::cout << trim(sst) << "|\n";
    assert(!std::isspace(*sst.begin()) && !std::isspace(last(sst)));

    sst = src;
    std::cout << trim_left(sst) << "|\n";
    assert(!std::isspace(*sst.begin()));

    sst = src;
    std::cout << trim_right(sst) << "|\n";
    assert(!std::isspace(last(sst)));
}
void trim_char_test(const char *src, char ch)
{
    assert(src);
    std::cout << "Trim char. Source: |" << src << "|\n";

    char st[32];
    assert(std::strlen(src) < sizeof st);

    std::strcpy(st, src);
    std::cout << trim(st, ch) << "|\n";
    assert(*st != ch && last(st) != ch);

    std::strcpy(st, src);
    std::cout << trim_left(st, ch) << "|\n";
    assert(*st != ch);

    std::strcpy(st, src);
    std::cout << trim_right(st, ch) << "|\n";
    assert(last(st) != ch);

    std::string sst;

    sst = src;
    std::cout << trim(sst, ch) << "|\n";
    assert(*sst.begin() != ch && last(sst) != ch);

    sst = src;
    std::cout << trim_left(sst, ch) << "|\n";
    assert(*sst.begin() != ch);

    sst = src;
    std::cout << trim_right(sst, ch) << "|\n";
    assert(last(sst) != ch);
}
void trim_set_test(const char *src, const char *set)
{
    assert(src);
    std::cout << "Trim set. Source: |" << src << "|\n";

    char st[32];
    assert(std::strlen(src) < sizeof st);

    std::strcpy(st, src);
    std::cout << trim(st, set) << "|\n";
    assert(not_in_set(*st, set) && not_in_set(last(st), set));

    std::strcpy(st, src);
    std::cout << trim_left(st, set) << "|\n";
    assert(not_in_set(*st, set));

    std::strcpy(st, src);
    std::cout << trim_right(st, set) << "|\n";
    assert(not_in_set(last(st), set));

    std::string sst;

    sst = src;
    std::cout << trim(sst, set) << "|\n";
    assert(not_in_set(*sst.begin(), set) && not_in_set(last(sst), set));

    sst = src;
    std::cout << trim_left(sst, set) << "|\n";
    assert(not_in_set(*sst.begin(), set));

    sst = src;
    std::cout << trim_right(sst, set) << "|\n";
    assert(not_in_set(last(sst), set));
}
void trimmed_default_test(const char *src)
{
    assert(src);
    std::cout << "Default trimmed. Source: |" << src << "|\n";
    std::string st;

    st = trimmed(src);
    assert(!std::isspace(*st.begin()) && !std::isspace(last(st)));
    std::cout << st << "|\n";

    st = trimmed_left(src);
    assert(!std::isspace(*st.begin()));
    std::cout << st << "|\n";

    st = trimmed_right(src);
    assert(!std::isspace(last(st)));
    std::cout << st << "|\n";
}
void trimmed_char_test(const char *src, char ch)
{
    assert(src);
    std::cout << "Trimmed char. Source: |" << src << "|\n";
    std::string st;

    st = trimmed(src, ch);
    assert(*st.begin() != ch && last(st) != ch);
    std::cout << st << "|\n";

    st = trimmed_left(src, ch);
    assert(*st.begin() != ch);
    std::cout << st << "|\n";

    st = trimmed_right(src, ch);
    assert(last(st) != ch);
    std::cout << st << "|\n";
}
void trimmed_set_test(const char *src, const char *set)
{
    assert(src);
    std::cout << "Trimmed set. Source: |" << src << "|\n";
    std::string st;

    st = trimmed(src, set);
    assert(not_in_set(*st.begin(), set) && not_in_set(last(st), set));
    std::cout << st << "|\n";

    st = trimmed_left(src, set);
    assert(not_in_set(*st.begin(), set));
    std::cout << st << "|\n";

    st = trimmed_right(src, set);
    assert(not_in_set(last(st), set));
    std::cout << st << "|\n";
}
void run()
{
    test_utils();

    trim_default_test(" \tabc  \t  ");
    std::cout << std::endl;
    trim_char_test("  abc   ", ' ');
    std::cout << std::endl;
    trim_set_test(" \tabc  \t  ", " \t\r\n\f");
    std::cout << std::endl;

    trimmed_default_test(" \tabc  \t  ");
    std::cout << std::endl;
    trimmed_char_test("  abc   ", ' ');
    std::cout << std::endl;
    trimmed_set_test(" \tabc  \t  ", " \t\r\n\f");
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
