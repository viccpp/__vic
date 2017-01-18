//
// $Id$
//

#include<__vic/fs.h>
#include<__vic/windows/throw_last_error.h>
#include<windows.h>

namespace __vic {

//----------------------------------------------------------------------------
uint64_t file_size(const char *path)
{
    WIN32_FILE_ATTRIBUTE_DATA attr;
    if(!::GetFileAttributesExA(path, GetFileExInfoStandard, &attr))
        windows::throw_last_error("GetFileAttributesEx");
    return (uint64_t(attr.nFileSizeHigh) << sizeof(DWORD)) | attr.nFileSizeLow;
}
//----------------------------------------------------------------------------

} // namespace
