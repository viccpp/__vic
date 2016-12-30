//
// $Id$
//

#include<__vic/date_time.h>
#include<__vic/string_buffer.h>

namespace __vic {

//----------------------------------------------------------------------------
// yy != 0 , mm - 1..12, dd - 1..{28..31}
void validate_date(int yy, int mm, int dd)
{
    if(yy == 0) throw invalid_date("Invalid year 0");
    if(mm < 1 || mm > 12) throw invalid_date(__vic::msg(32) <<
        "Invalid month " << mm);
    if(dd < 1 || dd > days_in_month(mm, yy)) throw invalid_date(__vic::msg(32) <<
        "Invalid day of month " << dd);
}
//----------------------------------------------------------------------------
// hh - 0..23, mi - 0..59, ss - 0..59
void validate_time(int hh, int mi, int ss)
{
    if(hh < 0 || hh > 23) throw invalid_date(__vic::msg(32) <<
        "Invalid hour " << hh);
    if(mi < 0 || mi > 59) throw invalid_date(__vic::msg(32) <<
        "Invalid minute " << mi);
    if(ss < 0 || ss > 59) throw invalid_date(__vic::msg(32) <<
        "Invalid second " << ss);
}
//----------------------------------------------------------------------------

} // namespace
