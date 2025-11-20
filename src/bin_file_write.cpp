//
// $Id$
//

#include<__vic/bin_file.h>
#include<__vic/windows/throw_last_error.h>
#include<windows.h>

namespace __vic {

//----------------------------------------------------------------------------
void bin_file::write_all(const void *buf, size_t n)
{
    for(;;)
    {
        DWORD to_write = ~DWORD(0);
        if(n < to_write) to_write = static_cast<DWORD>(n);
        DWORD written;
        if(!::WriteFile(hFile, buf, to_write, &written, nullptr))
            windows::throw_last_error("WriteFile");
        if(written == n) break;
        // Assert: written <= n
        n -= written;
    }
}
//----------------------------------------------------------------------------

} // namespace
