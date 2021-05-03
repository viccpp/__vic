//
// $Id$
//

#include<__vic/string_utils.h>
#include<__vic/set_of_chars.h>

namespace __vic {

namespace {
//----------------------------------------------------------------------------
class is_trash
{
    set_of_chars trash_chars;
public:
    explicit is_trash(const char *trash) : trash_chars(trash) {}
    bool operator()(char ch) const { return trash_chars.contains(ch); }
};
//----------------------------------------------------------------------------
} // namespace
//----------------------------------------------------------------------------
char *sift(char *st, const char *trash_chars)
{
    if(trash_chars) impl::sift_if(st, is_trash(trash_chars));
    return st;
}
//----------------------------------------------------------------------------
std::string &sift(std::string &st, const char *trash_chars)
{
    if(trash_chars) impl::sift_if(st, is_trash(trash_chars));
    return st;
}
//----------------------------------------------------------------------------

} // namespace
