#ifndef __VIC_USE_MODULES
#include<__vic/windows/wait_cursor.h>
#endif
#include<windows.h>
#ifdef __VIC_USE_MODULES
import std;
import __vic;
#endif

void wait_cursor_test(HCURSOR hCursor)
{
    __vic::windows::WaitCursor _(hCursor);
}
int main()
{
    // Check only compilation errors
}
