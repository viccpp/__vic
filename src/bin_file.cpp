//
// $Id$
//

#include<__vic/bin_file.h>
#include<__vic/windows/wchar.h>
#include<__vic/windows/throw_last_error.h>
#include<windows.h>

namespace __vic {

//----------------------------------------------------------------------------
bool bin_file::open_(
    const char *fname, DWORD dwDesiredAccess, DWORD dwCreationDisposition)
{
    hFile = ::CreateFileW(windows::utf8to16(fname), dwDesiredAccess,
        FILE_SHARE_READ | FILE_SHARE_DELETE, nullptr,
        dwCreationDisposition, FILE_ATTRIBUTE_NORMAL, nullptr);
    return is_open();
}
//----------------------------------------------------------------------------
void bin_file::close()
{
    if(!close_nt()) windows::throw_last_error("CloseHandle");
}
//----------------------------------------------------------------------------

} // namespace
