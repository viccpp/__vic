#ifndef __VIC_USE_MODULES
#include<__vic/windows/dc.h>
#endif
#include<windows.h>
#ifdef __VIC_USE_MODULES
import std;
import __vic;
#endif

void dc_test(__vic::windows::DC &dc)
{
    dc.Delete();
}
void client_dc_test(HWND hwnd)
{
    __vic::windows::ClientDC _(hwnd);
}
void paint_dc_test(HWND hwnd)
{
    __vic::windows::PaintDC _(hwnd);
}
int main()
{
    // Check only compilation errors
}
