//
// $Id$
//

#include<__vic/windows/dc.h>
#include<__vic/windows/throw_last_error.h>

namespace __vic { namespace windows {

//----------------------------------------------------------------------------
void DC::Select(HRGN hReg)
{
    // Usage of HGDI_ERROR in headers can be problematic for modular code
    if(::SelectObject(hdc, hReg) == HGDI_ERROR)
        throw_failed("SelectObject(HRGN)");
}
//----------------------------------------------------------------------------

}} // namespace
