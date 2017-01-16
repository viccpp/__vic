//
// $Id$
//

#include<__vic/str2num.h>
#include<stdexcept>

namespace __vic {

namespace impl {
//----------------------------------------------------------------------------
void throw_empty_integer()
{
    throw std::invalid_argument("Invalid integer: empty string");
}
//----------------------------------------------------------------------------
void throw_null_integer()
{
    throw std::invalid_argument("Invalid integer: null string");
}
//----------------------------------------------------------------------------
void throw_non_digit_char()
{
    throw std::invalid_argument("Invalid integer: non-digit char");
}
//----------------------------------------------------------------------------
void throw_integer_too_long()
{
    throw std::range_error("Integer value is too long");
}
//----------------------------------------------------------------------------
} // namespace

} // namespace
