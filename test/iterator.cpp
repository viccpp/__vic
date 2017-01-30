#include<__vic/iterator.h>
#include<__vic/defs.h>
#include<iostream>
#include<exception>
#include<cassert>
#include<list>

void run_tests()
{
    const int arr[] = { 0, 1, 2 };

    assert(__vic::begin(arr) == arr);
    assert(__vic::end(arr) == arr + __vic::array_size(arr));

    assert(__vic::next(arr) == arr + 1);
    assert(__vic::next(arr, 2) == arr + 2);

    assert(__vic::prev(__vic::next(arr)) == arr);
    assert(__vic::prev(__vic::next(arr, 2), 2) == arr);

    const int *p = arr;
    __vic::advance(p, __vic::end(arr), 2);
    assert(p == arr + 2);
    __vic::advance(p, __vic::end(arr), 10);
    assert(p == __vic::end(arr));

    std::list<int> l(__vic::begin(arr), __vic::end(arr));
    assert(l.size() == __vic::array_size(arr));
    std::list<int>::iterator it = l.begin();
    __vic::advance(it, l.end(), 2);
    assert(*it == arr[2]);
    __vic::advance(it, l.end(), 10);
    assert(it == l.end());
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
