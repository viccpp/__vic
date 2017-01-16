//
// $Id$
//

#include<__vic/date_time.h>

namespace __vic {

//----------------------------------------------------------------------------
inline long ceil_divisible(unsigned n, unsigned divisor)
{
    unsigned rem = n % divisor;
    return rem == 0 ? n : n + (divisor - rem);
}
//----------------------------------------------------------------------------
inline long leap_years_between(unsigned year1, unsigned year2)
{
    return (ceil_divisible(year2, 4)   - ceil_divisible(year1, 4))   / 4L   -
           (ceil_divisible(year2, 100) - ceil_divisible(year1, 100)) / 100L +
           (ceil_divisible(year2, 400) - ceil_divisible(year1, 400)) / 400L;
}
//----------------------------------------------------------------------------
long days_between_years(unsigned year1, unsigned year2)
{
    return (static_cast<long>(year2) - static_cast<long>(year1)) * 365L +
        leap_years_between(year1, year2);
}
//----------------------------------------------------------------------------

} // namespace
