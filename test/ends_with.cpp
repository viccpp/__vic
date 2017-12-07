#include<__vic/string_utils.h>
#include<iostream>
#include<exception>
#include<cassert>

void run_tests()
{
    using __vic::ends_with;
    const std::string sample("sample");

    assert(ends_with(sample, 'e'));
    assert(ends_with(sample, "le"));
    assert(ends_with(sample, std::string("le")));

    assert(ends_with("sample", 'e'));
    assert(ends_with("sample", "le"));
    assert(ends_with("sample", std::string("le")));

    assert(!ends_with(sample, 's'));
    assert(!ends_with(sample, "sa"));
    assert(!ends_with(sample, std::string("sa")));

    assert(!ends_with("sample", 's'));
    assert(!ends_with("sample", "sa"));
    assert(!ends_with("sample", std::string("sa")));

    assert(ends_with(sample, ""));
    assert(ends_with("", ""));
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
