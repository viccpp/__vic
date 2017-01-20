//
// $Id$
//

#include<__vic/bin_file.h>
#include<__vic/error.h>
#include<cstdio>

namespace __vic {

//----------------------------------------------------------------------------
size_t bin_file::read_max(void *buf, size_t n)
{
    size_t res = std::fread(buf, 1, n , f);
    using namespace std; // ferror can be implemented as a macro
    if(res == n || !ferror(f)) return res;
    throw exception("I/O error: read failed");
}
//----------------------------------------------------------------------------

} // namespace
