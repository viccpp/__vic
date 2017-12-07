#include<__vic/string_utils.h>
#include<iostream>
#include<exception>
#include<cassert>

void run_tests()
{
    using __vic::starts_with;
    const std::string sample("sample");

    assert(starts_with(sample, 's'));
    assert(starts_with(sample, "sa"));
    assert(starts_with(sample, std::string("sa")));

    assert(starts_with("sample", 's'));
    assert(starts_with("sample", "sa"));
    assert(starts_with("sample", "sa", 2));

    assert(!starts_with(sample, 'a'));
    assert(!starts_with(sample, "am"));
    assert(!starts_with(sample, std::string("am")));

    assert(!starts_with("sample", 'a'));
    assert(!starts_with("sample", "am"));
    assert(!starts_with("sample", "am", 2));

    assert(starts_with(sample, ""));
    assert(starts_with("", ""));
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
