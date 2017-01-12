#include<__vic/set_of_chars.h>
#include<iostream>
#include<exception>
#include<cassert>

void run_tests()
{
    __vic::set_of_chars set;
    for(int c = 0; c < 256; c++)
        assert(!set.contains((unsigned char) c));
    set.add('a');
    assert(set.contains('a'));
    assert(!set.contains('b'));
    set.add('b');
    assert(set.contains('a') && set.contains('b'));
    set.remove('a');
    assert(!set.contains('a') && set.contains('b'));

    set.assign("123");
    assert(set.contains('1'));
    assert(set.contains('2'));
    assert(set.contains('3'));
    assert(!set.contains('a'));
    assert(!set.contains('b'));
    assert(!set.contains('0'));
    assert(!set.contains('4'));

#if __cpp_initializer_lists
    set.assign({'1', '2', '3'});
    assert(set.contains('1'));
    assert(set.contains('2'));
    assert(set.contains('3'));
    assert(!set.contains('a'));
    assert(!set.contains('b'));
    assert(!set.contains('0'));
    assert(!set.contains('4'));
#endif
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
