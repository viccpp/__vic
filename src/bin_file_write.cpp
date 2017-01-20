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
        DWORD written;
        if(!::WriteFile(hFile, buf, n, &written, nullptr))
            windows::throw_last_error("WriteFile");
        if(written == n) break;
        // Assert: written <= n
        n -= written;
    }
}
//----------------------------------------------------------------------------

} // namespace
