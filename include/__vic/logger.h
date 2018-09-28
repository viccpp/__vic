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
    __VIC_SCOPED_ENUM_BEGIN(severity)
    {
        trace,
        debug,
        info,       // Default severity
        warning,    // Insignificant error
        error,      // Severe error. Application can continue running
        fatal       // Critical unrecoverable error. Application can't
                    // continue running
    }
    __VIC_SCOPED_ENUM_END(severity)
    struct output
    {
        virtual void publish_record(severity_t , const char * , size_t ) = 0;
    protected:
        ~output() __VIC_DEFAULT_CTR
    };
    struct settings_t
    {
        struct output *out;
        severity_t lvl;
        struct output &output() const { return *out; }
        severity_t level() const { return lvl; }
    };
    class record;

    explicit logger(output & , severity_t = severity::info);
    explicit logger(settings_t );
    ~logger();

    severity_t level() const { return log_level; }
    void level(severity_t new_level) { log_level = new_level; }
    settings_t settings() const { settings_t s = {out, level()}; return s; }

    output &reset_output(output &out)
    {
        output &old = *this->out;
        this->out = &out;
        return old;
    }
    output &get_output() { return *out; }
    const output &get_output() const { return *out; }

    void message(severity_t , const char * , size_t );
    void message(severity_t , const char * );
    void message(severity_t s, const std::string &msg)
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

    bool trace_visible() const { return level() <= severity::trace; }
    bool debug_visible() const { return level() <= severity::debug; }
    bool info_visible() const { return level() <= severity::info; }
    bool warning_visible() const { return level() <= severity::warning; }
    bool error_visible() const { return level() <= severity::error; }
    bool fatal_visible() const { return level() <= severity::fatal; }
private:
    severity_t log_level;
    output *out;

    // current record buffer
    static __VIC_CONSTEXPR_VAR size_t lo_water_mark = 256, hi_water_mark = 4096;
    string_buffer cur_msg;
    severity_t cur_severity;
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
    record(logger &log, severity_t severity) : log(log)
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
inline const char *to_string(logger::severity_t s)
{
    extern const char * const logger_severity_strs[];
    return logger_severity_strs[int(s)];
}
//----------------------------------------------------------------------------

} // namespace

#endif // header guard
