//
// $Id$
//

#include<__vic/bin_file.h>
#include<__vic/windows/throw_last_error.h>
#include<windows.h>

namespace __vic {

//----------------------------------------------------------------------------
bool bin_file::open_append(const char *fname)
{
    if(!open_(fname, GENERIC_WRITE, append)) return false;
    if(::SetFilePointer(hFile, 0, 0, FILE_END) == INVALID_SET_FILE_POINTER)
        windows::throw_last_error("SetFilePointer");
    return true;
}
//----------------------------------------------------------------------------

} // namespace
