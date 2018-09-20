//
// $Id$
//

#include<__vic/logger.h>
#include<cstring>

namespace __vic {

extern const char * const logger_severity_strs[] =
    { "TRACE", "DEBUG", "INFO", "WARNING", "ERROR", "FATAL" };
//----------------------------------------------------------------------------
logger::logger(output &out, severity_t level)
:
    log_level(level), out(&out),
    cur_msg(lo_water_mark), rec_objs_count(0)
{
}
//----------------------------------------------------------------------------
logger::logger(settings_t s)
:
    log_level(s.level()), out(&s.output()),
    cur_msg(lo_water_mark), rec_objs_count(0)
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
void logger::message(severity_t s, const char *msg)
{
    if(s >= level()) out->publish_record(s, msg, std::strlen(msg));
}
//----------------------------------------------------------------------------
void logger::_flush()
{
    // Micro-optimization: Avoiding message() fuction call
    //message(cur_severity, cur_msg.data(), cur_msg.length());
    if(cur_severity >= level())
        out->publish_record(cur_severity, cur_msg.data(), cur_msg.length());

    cur_msg.clear();
    // prevent uncontrolled buffer growth
    if(cur_msg.capacity() > hi_water_mark)
        string_buffer(lo_water_mark).swap(cur_msg);
}
//----------------------------------------------------------------------------

} // namespace
