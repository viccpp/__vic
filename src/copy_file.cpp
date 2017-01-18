//
// $Id$
//

#include<__vic/fs.h>
#include<__vic/windows/throw_last_error.h>
#include<windows.h>

//----------------------------------------------------------------------------
void __vic::copy_file(const char *src_path, const char *dest_path, bool replace)
{
    if(!::CopyFileA(src_path, dest_path, !replace))
        windows::throw_last_error("CopyFile");
}
//----------------------------------------------------------------------------
