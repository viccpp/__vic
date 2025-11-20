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
    DWORD to_read = ~DWORD(0);
    if(n < to_read) to_read = static_cast<DWORD>(n);
    DWORD read;
    if(!::ReadFile(hFile, buf, to_read, &read, nullptr))
        windows::throw_last_error("ReadFile");
    return read;
}
//----------------------------------------------------------------------------
size_t bin_file::read_max(void *buf, size_t n)
{
    size_t res = 0;
    do {
        DWORD to_read = ~DWORD(0);
        if(n < to_read) to_read = static_cast<DWORD>(n);
        DWORD read;
        if(!::ReadFile(hFile, buf, to_read, &read, nullptr))
            windows::throw_last_error("ReadFile");
        if(read == 0) break;
        res += read;
    } while(res < n);
    return res;
}
//----------------------------------------------------------------------------

} // namespace
