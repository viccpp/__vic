#include<__vic/defs.h>
#include<__vic/object_pool.h>
#include<iostream>
#include<exception>
#include<string>
#include<cassert>

namespace tests {

class C : private __vic::non_copyable
{
    std::string name_;
public:
    explicit C(const std::string &name) : name_(name) {}
    std::string name() const { return name_; }
};

void run()
{
    __vic::object_pool<C> pool(2);
    std::cout << "Pool size: " << pool.size() << '\n';

    new(pool.alloc()) C("C1");
    assert(pool.size() == 0);
    pool.push_allocated();
    assert(pool.size() == 1);

#if __cpp_rvalue_references && __cpp_variadic_templates
    pool.emplace("C2");
#else
    new(pool.alloc()) C("C2");
    pool.push_allocated();
#endif

    assert(pool.size() == 2);
    std::cout << "Pool size: " << pool.size() << '\n';
    std::cout << "Pool access by index:\n";
    for(unsigned i = 0; i < pool.size(); i++)
        std::cout << pool[i].name() << ' ';
    std::cout << '\n';
    std::cout << "Pool access by iterator:\n";
    for(__vic::object_pool<C>::const_iterator it =
            pool.cbegin(); it != pool.cend(); ++it)
        std::cout << it->name() << ' ';
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
