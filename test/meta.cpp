#include<__vic/meta.h>
#include<iostream>
#include<exception>
#include<cassert>

namespace tests {

void run()
{
    assert(( __vic::is_same<int, int>::value));
    assert((!__vic::is_same<int, short>::value));
    assert((!__vic::is_same<int, const int>::value));

    assert( __vic::is_const<const int>::value);
    assert(!__vic::is_const<int>::value);

    assert( __vic::is_signed_integer<int>::value);
    assert( __vic::is_signed_integer<signed char>::value);
    assert(!__vic::is_signed_integer<unsigned>::value);
    assert(!__vic::is_signed_integer<double>::value);
    assert( __vic::is_unsigned_integer<unsigned>::value);
    assert(!__vic::is_unsigned_integer<int>::value);
    assert( __vic::is_unsigned_integer<unsigned char>::value);

    assert((__vic::is_same<
        __vic::remove_const<const int>::type,
        int>::value));
    assert((__vic::is_same<
        __vic::remove_const<int>::type,
        int>::value));

    assert((__vic::is_same<
        __vic::remove_cv<const int>::type,
        int>::value));
    assert((__vic::is_same<
        __vic::remove_cv<volatile int>::type,
        int>::value));
    assert((__vic::is_same<
        __vic::remove_cv<const volatile int>::type,
        int>::value));
    assert((__vic::is_same<
        __vic::remove_const<int>::type,
        int>::value));

    assert((__vic::is_same<
        __vic::remove_pointer<int *>::type,
        int>::value));
    assert((__vic::is_same<
        __vic::remove_pointer<int>::type,
        int>::value));
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
