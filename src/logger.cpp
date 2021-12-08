//
// $Id$
//

#include<__vic/logger.h>
#include<cstring>

namespace __vic {

//----------------------------------------------------------------------------
logger::logger(output &out, severity_t level)
:
    log_level(level), out(&out),
    cur_msg(min_buffer_size), rec_objs_count(0)
{
}
//----------------------------------------------------------------------------
logger::logger(settings_t s)
:
    log_level(s.level()), out(&s.output()),
    cur_msg(min_buffer_size), rec_objs_count(0)
{
}
//----------------------------------------------------------------------------
logger::~logger()
{
}
//----------------------------------------------------------------------------
void logger::message(severity_t s, const char *msg, size_t msg_len)
{
    if(s >= level()) out->publish_record(s, msg, msg_len);
}
//----------------------------------------------------------------------------
#if !__cpp_lib_string_view
void logger::message(severity_t s, const char *msg)
{
    if(s >= level()) out->publish_record(s, msg, std::strlen(msg));
}
#endif
//----------------------------------------------------------------------------
void logger::_flush()
{
    // Micro-optimization: Avoiding message() fuction call
    //message(cur_severity, cur_msg.data(), cur_msg.length());
    if(cur_severity >= level())
        out->publish_record(cur_severity, cur_msg.data(), cur_msg.length());
    cur_msg.clear();
    //shrink_buffer(hi_water_mark); // prevent uncontrolled buffer growth
}
//----------------------------------------------------------------------------

} // namespace
