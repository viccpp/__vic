// Date and time utils
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_DATE_TIME_H
#define __VIC_DATE_TIME_H

#include<__vic/defs.h>
#include<__vic/error.h>

namespace __vic {

//----------------------------------------------------------------------------
__VIC_CONSTEXPR_FUNC bool is_leap_year(int year)
{
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}
//----------------------------------------------------------------------------

// 1st arg: month 1..12 (0 will be returned otherwise)
// 2nd arg: year is used only if mon == 2
int days_in_month(int , int ) noexcept;

// Returns the difference in days between the beginning
// of the 2nd year and the beginning of the 1st year
// Year can't be 0!!!
long days_between_years(unsigned , unsigned );

//////////////////////////////////////////////////////////////////////////////
struct invalid_date : public exception
{
    explicit invalid_date(const char *msg) : exception(msg) {}
};
//////////////////////////////////////////////////////////////////////////////
// yy != 0, mm - 1..12, dd - 1..{28..31}, hh - 0..23, mi - 0..59, ss - 0..59
void validate_date(int yy, int mm, int dd);
void validate_time(int hh, int mi, int ss);
inline void validate_date_time(int yy, int mm, int dd, int hh, int mi, int ss)
{
    validate_date(yy, mm, dd);
    validate_time(hh, mi, ss);
}

} // namespace

#endif // header guard
