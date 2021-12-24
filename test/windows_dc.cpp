#include<__vic/windows/dc.h>

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
