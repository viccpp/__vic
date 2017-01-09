//
// $Id$
//

#include<__vic/string_ops.h>
#include<cstring>

namespace __vic {

namespace {
//----------------------------------------------------------------------------
class is_trash
{
    const char *trash_chars;
public:
    explicit is_trash(const char *trash) : trash_chars(trash) {}
    bool operator()(char ch) const { return std::strchr(trash_chars, ch); }
};
//----------------------------------------------------------------------------
} // namespace
//----------------------------------------------------------------------------
char *sift(char *st, const char *trash_chars)
{
    return impl::sift_if(st, is_trash(trash_chars));
}
//----------------------------------------------------------------------------
std::string &sift(std::string &st, const char *trash_chars)
{
    return impl::sift_if(st, is_trash(trash_chars));
}
//----------------------------------------------------------------------------

} // namespace
