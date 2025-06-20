#ifndef __VIC_USE_MODULES
#include<__vic/windows/shadow_dc.h>
#endif
#ifdef __VIC_USE_MODULES
import std;
import __vic;
#endif

void shadow_dc_test()
{
    __vic::windows::ShadowDC dc;
    (void) dc;
}
int main()
{
    // Check only compilation errors
}
