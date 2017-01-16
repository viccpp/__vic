// Logger front-end
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_LOGGER_H
#define __VIC_LOGGER_H

#include<__vic/defs.h>
#include<__vic/string_buffer.h>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
// Abstract base class
class logger : private non_copyable
{
public:
#if __cplusplus >= 201103L // C++11
    enum class severity
#else // C++98
    struct severity { enum type_
#endif
    {
        trace,
        debug,
        info,       // Default severity
        warning,    // Insignificant error
        error,      // Severe error. Application can continue running
        fatal       // Critical unrecoverable error. Application can't
                    // continue running
    };
#if __cplusplus >= 201103L
    using message_severity = severity;
#else
    };
    typedef severity::type_ message_severity;
#endif
    class record;

    explicit logger(message_severity level = severity::info)
        : log_level(level), cur_msg(lo_water_mark), rec_objs_count(0) {}
    virtual ~logger() __VIC_DEFAULT_CTR

    message_severity level() const { return log_level; }
    void level(message_severity new_level) { log_level = new_level; }

    void message(message_severity , const char * , size_t );
    void message(message_severity , const char * );
    void message(message_severity s, const std::string &msg)
        { message(s, msg.data(), msg.length()); }

    void trace(const char *msg) { message(severity::trace, msg); }
    void debug(const char *msg) { message(severity::debug, msg); }
    void info(const char *msg) { message(severity::info, msg); }
    void warning(const char *msg) { message(severity::warning, msg); }
    void error(const char *msg) { message(severity::error, msg); }
    void fatal(const char *msg) { message(severity::fatal, msg); }

    void trace(const std::string &msg) { message(severity::trace, msg); }
    void debug(const std::string &msg) { message(severity::debug, msg); }
    void info(const std::string &msg) { message(severity::info, msg); }
    void warning(const std::string &msg) { message(severity::warning, msg); }
    void error(const std::string &msg) { message(severity::error, msg); }
    void fatal(const std::string &msg) { message(severity::fatal, msg); }

    record trace();
    record debug();
    record info();
    record warning();
    record error();
    record fatal();

    bool accepts_trace() const { return level() <= severity::trace; }
    bool accepts_debug() const { return level() <= severity::debug; }
    bool accepts_info() const { return level() <= severity::info; }
    bool accepts_warning() const { return level() <= severity::warning; }
    bool accepts_error() const { return level() <= severity::error; }
    bool accepts_fatal() const { return level() <= severity::fatal; }

    static const char *to_string(message_severity s) { return sev_strs[int(s)]; }
protected:
    virtual void publish_record(message_severity , const char * , size_t ) = 0;
private:
    static const char * const sev_strs[];
    message_severity log_level;

    // current record buffer
    static __VIC_CONSTEXPR_VAR size_t lo_water_mark = 256, hi_water_mark = 4096;
    string_buffer cur_msg;
    message_severity cur_severity;
    size_t rec_objs_count;
    template<class T> void _put(const T &v) { cur_msg << v; }
    void _append(const char *s, size_t len) { cur_msg.append(s, len); }
    void _flush();
    void _inc_count() { rec_objs_count++; }
    void _dec_count() { if(--rec_objs_count == 0) _flush(); }
};
//////////////////////////////////////////////////////////////////////////////
class logger::record
{
    logger &log;
public:
    record(logger &log, message_severity severity) : log(log)
    {
        log.cur_severity = severity;
        log._inc_count();
    }
    record(const record &o) : log(o.log) { log._inc_count(); }
    ~record() { log._dec_count(); }

    record append(const char *s, size_t n) { log._append(s,n); return *this; }

    template<class T>
    record operator<<(const T &v) { log._put(v); return *this; }
};
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
inline logger::record logger::trace() { return record(*this, severity::trace); }
inline logger::record logger::debug() { return record(*this, severity::debug); }
inline logger::record logger::info() { return record(*this, severity::info); }
inline logger::record logger::warning() { return record(*this, severity::warning); }
inline logger::record logger::error() { return record(*this, severity::error); }
inline logger::record logger::fatal() { return record(*this, severity::fatal); }
//----------------------------------------------------------------------------

} // namespace

#endif // header guard
