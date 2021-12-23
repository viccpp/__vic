#include<__vic/windows/wait_cursor.h>

void wait_cursor_test(HCURSOR hCursor)
{
    __vic::windows::WaitCursor _(hCursor);
}
int main()
{
    // Check only compilation errors
}
