//
// $Id$
//

#include<__vic/logger.h>
#include<cstring>

namespace __vic {

const char * const logger::sev_strs[] =
    { "TRACE", "DEBUG", "INFO", "WARNING", "ERROR", "FATAL" };
//----------------------------------------------------------------------------
void logger::message(severity_t s, const char *msg, size_t msg_len)
{
    if(s >= level()) publish_record(s, msg, msg_len);
}
//----------------------------------------------------------------------------
void logger::message(severity_t s, const char *msg)
{
    if(s >= level()) publish_record(s, msg, std::strlen(msg));
}
//----------------------------------------------------------------------------
void logger::_flush()
{
    // Micro-optimization: Avoiding message() fuction call
    //message(cur_severity, cur_msg.data(), cur_msg.length());
    if(cur_severity >= level())
        publish_record(cur_severity, cur_msg.data(), cur_msg.length());

    cur_msg.clear();
    // prevent uncontrolled buffer growth
    if(cur_msg.capacity() > hi_water_mark)
        string_buffer(lo_water_mark).swap(cur_msg);
}
//----------------------------------------------------------------------------

} // namespace
