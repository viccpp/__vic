//
// $Id$
//

#include<__vic/logger.h>
#include<iterator>

namespace __vic {

#if __cpp_lib_format >= 202106L
//----------------------------------------------------------------------------
void logger::vformat_(
    severity_t s, std::string_view fmt, std::format_args args)
{
    std::vformat_to(std::back_inserter(cur_msg), fmt, args);
    out->publish_record(s, cur_msg.data(), cur_msg.length());
    cur_msg.clear();
}
//----------------------------------------------------------------------------
#endif

} // namespace
