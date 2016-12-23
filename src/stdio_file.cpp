//
// $Id$
//

#include<__vic/io.h>
#include<__vic/error.h>

namespace __vic {

//----------------------------------------------------------------------------
void stdio_file::close()
{
    int st = std::fclose(fp);
    fp = nullptr;
    if(st) throw exception("std::fclose");
}
//----------------------------------------------------------------------------

} // namespace
