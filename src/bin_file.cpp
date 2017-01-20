//
// $Id$
//

#include<__vic/bin_file.h>
#include<cstdio>

namespace __vic {

//----------------------------------------------------------------------------
bool bin_file::open_(const char *fname, char mode_char)
{
    char mode[3] = { mode_char, 'b', '\x0' };
    if(f.open(fname, mode)) std::setbuf(f, nullptr);
    return is_open();
}
//----------------------------------------------------------------------------

} // namespace
