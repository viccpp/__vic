//
// $Id$
//

#include<__vic/fs.h>
#include<__vic/windows/wchar.h>
#include<__vic/windows/throw_last_error.h>
#include<windows.h>

//----------------------------------------------------------------------------
void __vic::copy_file(const char *src_path, const char *dest_path, bool replace)
{
    using windows::utf8to16;
    if(!::CopyFileW(utf8to16(src_path), utf8to16(dest_path), !replace))
        windows::throw_last_error("CopyFile");
}
//----------------------------------------------------------------------------
