//
// $Id$
//

#include<__vic/date_time.h>

namespace __vic {

//----------------------------------------------------------------------------
int days_in_month(int mon, int year) noexcept
{
    //  1   2    3  4  5  6  7  8  9 10 11 12
    // 31 28/29 31 30 31 30 31 31 30 31 30 31
    switch(mon)
    {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return is_leap_year(year) ? 29 : 28;
    }
    return 0;
}
//----------------------------------------------------------------------------

} // namespace
