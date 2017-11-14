#include<__vic/ascii.h>
#include<exception>
#include<iostream>
#include<cassert>

#ifdef isascii
#undef isascii
#endif

namespace tests {

namespace ascii = __vic::ascii;

void run()
{
    assert( ascii::islower('a'));
    assert(!ascii::islower('A'));
    assert(!ascii::islower('.'));

    assert(!ascii::isupper('x'));
    assert( ascii::isupper('X'));
    assert(!ascii::isupper('.'));

    assert( ascii::isascii('A'));
    assert(!ascii::isascii('\x80'));
    assert(!ascii::isascii('\xFF'));

    assert(ascii::tolower('Z') == 'z');
    assert(ascii::tolower('z') == 'z');
    assert(ascii::tolower('1') == '1');
    assert(ascii::tolower('\xF0') == '\xF0');

    assert(ascii::toupper('z') == 'Z');
    assert(ascii::toupper('Z') == 'Z');
    assert(ascii::toupper('1') == '1');
    assert(ascii::toupper('\xF0') == '\xF0');

    assert( ascii::equal_icase('a', 'a'));
    assert( ascii::equal_icase('a', 'A'));
    assert(!ascii::equal_icase('a', 'b'));
    assert(!ascii::equal_icase('.', ','));

    assert(ascii::todigit(1) == '1');

    assert(ascii::toxdigit_upper(1) == '1');
    assert(ascii::toxdigit_lower(1) == '1');
    assert(ascii::toxdigit_upper(10) == 'A');
    assert(ascii::toxdigit_lower(10) == 'a');

    assert(ascii::digit_to_number('5') == 5);
    assert(ascii::digit_to_number('A') == -1);

    for(int i = 0; i < 256; i++)
        std::cout << ascii::xdigit_to_number(i) << ' ';
    std::cout << '\n';
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
