//
// $Id$
//

#include<__vic/stdio_file.h>
#include<__vic/throw_errno.h>

namespace __vic {

//----------------------------------------------------------------------------
void stdio_file::close()
{
    int st = std::fclose(fp);
    fp = nullptr;
    if(st) throw_errno("std::fclose");
}
//----------------------------------------------------------------------------

} // namespace
