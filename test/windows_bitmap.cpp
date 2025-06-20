#ifndef __VIC_USE_MODULES
#include<__vic/windows/bitmap.h>
#endif
#ifdef __VIC_USE_MODULES
import std;
import __vic;
#endif

void bitmap_test()
{
    __vic::windows::Bitmap bmp;
    (void) bmp;
}
int main()
{
    // Check only compilation errors
}
