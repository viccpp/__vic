//
// $Id$
//

#include<__vic/string_utils.h>
#include<__vic/char_predicates.h>

namespace __vic {

//----------------------------------------------------------------------------
char *sift(char *st, const set_of_chars &trash_chars)
{
    return sift_if(st, is_one_of_chars(trash_chars));
}
//----------------------------------------------------------------------------
std::string &sift(std::string &st, const set_of_chars &trash_chars)
{
    return sift_if(st, is_one_of_chars(trash_chars));
}
//----------------------------------------------------------------------------

} // namespace
