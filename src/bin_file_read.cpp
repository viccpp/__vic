//
// $Id$
//

#include<__vic/bin_file.h>
#include<__vic/windows/throw_last_error.h>
#include<windows.h>

namespace __vic {

//----------------------------------------------------------------------------
size_t bin_file::read_some(void *buf, size_t n)
{
    DWORD read;
    if(!::ReadFile(hFile, buf, n, &read, nullptr))
        windows::throw_last_error("ReadFile");
    return read;
}
//----------------------------------------------------------------------------
size_t bin_file::read_max(void *buf, size_t n)
{
    size_t res = 0;
    do {
        DWORD read;
        if(!::ReadFile(hFile, buf, n, &read, nullptr))
            windows::throw_last_error("ReadFile");
        if(read == 0) break;
        res += read;
    } while(res < n);
    return res;
}
//----------------------------------------------------------------------------

} // namespace
