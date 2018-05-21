#include<__vic/type_traits.h>
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

    assert((__vic::is_same<
        __vic::remove_cvref<const int &>::type,
        int>::value));

#if __cpp_variadic_templates && __cpp_alias_templates
    assert((__vic::is_same<
        __vic::make_index_sequence<4>,
        __vic::index_sequence<0, 1, 2, 3>
    >::value));
    assert((__vic::is_same<
        __vic::make_index_sequence<0>,
        __vic::index_sequence<>
    >::value));
    //using huge_sequence = __vic::make_index_sequence<4096>;
#endif
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
