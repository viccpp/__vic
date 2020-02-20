#include<__vic/defs.h>
#include<__vic/fixed_vector.h>
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
    __vic::fixed_vector<C> v(2);
    std::cout << "Vector size: " << v.size() << '\n';

    new(v.alloc()) C("C1");
    assert(v.size() == 0);
    v.push_allocated();
    assert(v.size() == 1);

#if __cpp_rvalue_references && __cpp_variadic_templates
    v.emplace_back("C2");
#else
    new(v.alloc()) C("C2");
    v.push_allocated();
#endif

    assert(v.size() == 2);
    std::cout << "Vector size: " << v.size() << '\n';
    std::cout << "Access by index:\n";
    for(unsigned i = 0; i < v.size(); i++)
        std::cout << v[i].name() << ' ';
    std::cout << '\n';
    std::cout << "Access by iterator:\n";
    for(__vic::fixed_vector<C>::const_iterator it =
            v.cbegin(); it != v.cend(); ++it)
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
