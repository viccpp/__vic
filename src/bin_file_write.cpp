//
// $Id$
//

#include<__vic/bin_file.h>
#include<__vic/error.h>
#include<cstdio>

namespace __vic {

//----------------------------------------------------------------------------
void bin_file::write_all(const void *buf, size_t n)
{
    if(std::fwrite(buf, 1, n , f) != n)
        throw exception("I/O error: write failed");
}
//----------------------------------------------------------------------------

} // namespace
