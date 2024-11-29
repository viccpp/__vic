//
// $Id$
//

#include<__vic/fs.h>
#include<__vic/windows/wchar.h>
#include<__vic/windows/throw_last_error.h>
#include<windows.h>

namespace __vic {

//----------------------------------------------------------------------------
void copy_file(const wchar_t *src_path, const wchar_t *dest_path, bool replace)
{
    if(!::CopyFileW(src_path, dest_path, !replace))
        windows::throw_last_error("CopyFile");
}
//----------------------------------------------------------------------------
void copy_file(const char *src_path, const char *dest_path, bool replace)
{
    using windows::utf8to16;
    copy_file(utf8to16(src_path), utf8to16(dest_path), replace);
}
//----------------------------------------------------------------------------

} // namespace
