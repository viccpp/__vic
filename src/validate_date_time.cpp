//
// $Id$
//

#include<__vic/date_time.h>
#include<__vic/string_buffer.h>

namespace __vic {

//----------------------------------------------------------------------------
// y != 0 , m - 1..12, d - 1..{28..31}
void validate_date(int y, int m, int d)
{
    if(y == 0) throw invalid_date("Invalid year 0");
    if(m < 1 || m > 12) throw invalid_date(__vic::msg(32) <<
        "Invalid month " << m);
    if(d < 1 || d > days_in_month(m, y)) throw invalid_date(__vic::msg(32) <<
        "Invalid day of month " << d);
}
//----------------------------------------------------------------------------
// h - 0..23, m - 0..59, s - 0..59
void validate_time(int h, int m, int s)
{
    if(h < 0 || h > 23) throw invalid_date(__vic::msg(32) <<
        "Invalid hours " << h);
    if(m < 0 || m > 59) throw invalid_date(__vic::msg(32) <<
        "Invalid minutes " << m);
    if(s < 0 || s > 59) throw invalid_date(__vic::msg(32) <<
        "Invalid seconds " << s);
}
//----------------------------------------------------------------------------

} // namespace
