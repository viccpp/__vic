// Logger front-end
//
// Platform: ISO C++ 98/11/17
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_LOGGER_H
#define __VIC_LOGGER_H

#include<__vic/defs.h>
#include<__vic/string_buffer.h>
#if __has_include(<string_view>)
#include<string_view>
#endif

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
class logger : private non_copyable
{
public:
    __VIC_SCOPED_ENUM_UT_BEGIN(severity, unsigned char)
    {
        trace,
        debug,
        info,       // Default severity
        notice,     // Normal but significant event
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

    static __VIC_CONSTEXPR_VAR size_t min_buffer_size = 256;
    void shrink_buffer(size_t limit)
    {
        // assert(cur_msg.empty());
        if(cur_msg.capacity() > limit)
            string_buffer(min_buffer_size).swap(cur_msg);
    }

    void message(severity_t , const char * , size_t );
#if __cpp_lib_string_view
    void message(severity_t s, std::string_view msg)
        { message(s, msg.data(), msg.length()); }

    void trace(std::string_view msg) { message(severity::trace, msg); }
    void debug(std::string_view msg) { message(severity::debug, msg); }
    void info(std::string_view msg) { message(severity::info, msg); }
    void notice(std::string_view msg) { message(severity::notice, msg); }
    void warning(std::string_view msg) { message(severity::warning, msg); }
    void error(std::string_view msg) { message(severity::error, msg); }
    void fatal(std::string_view msg) { message(severity::fatal, msg); }
#else
    void message(severity_t , const char * );
    void message(severity_t s, const std::string &msg)
        { message(s, msg.data(), msg.length()); }

    void trace(const char *msg) { message(severity::trace, msg); }
    void debug(const char *msg) { message(severity::debug, msg); }
    void info(const char *msg) { message(severity::info, msg); }
    void notice(const char *msg) { message(severity::notice, msg); }
    void warning(const char *msg) { message(severity::warning, msg); }
    void error(const char *msg) { message(severity::error, msg); }
    void fatal(const char *msg) { message(severity::fatal, msg); }

    void trace(const std::string &msg) { message(severity::trace, msg); }
    void debug(const std::string &msg) { message(severity::debug, msg); }
    void info(const std::string &msg) { message(severity::info, msg); }
    void notice(const std::string &msg) { message(severity::notice, msg); }
    void warning(const std::string &msg) { message(severity::warning, msg); }
    void error(const std::string &msg) { message(severity::error, msg); }
    void fatal(const std::string &msg) { message(severity::fatal, msg); }
#endif
    record trace();
    record debug();
    record info();
    record notice();
    record warning();
    record error();
    record fatal();

    bool trace_visible() const { return level() <= severity::trace; }
    bool debug_visible() const { return level() <= severity::debug; }
    bool info_visible() const { return level() <= severity::info; }
    bool notice_visible() const { return level() <= severity::notice; }
    bool warning_visible() const { return level() <= severity::warning; }
    bool error_visible() const { return level() <= severity::error; }
    bool fatal_visible() const { return level() <= severity::fatal; }
private:
    severity_t log_level;
    output *out;

    // current record buffer
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
inline logger::record logger::notice() { return record(*this, severity::notice); }
inline logger::record logger::warning() { return record(*this, severity::warning); }
inline logger::record logger::error() { return record(*this, severity::error); }
inline logger::record logger::fatal() { return record(*this, severity::fatal); }
//----------------------------------------------------------------------------
inline const char *to_string(logger::severity_t s)
{
    extern const char * const logger_severity_strs[];
    return logger_severity_strs[static_cast<int>(s)];
}
//----------------------------------------------------------------------------
#if __cpp_lib_string_view
constexpr std::string_view to_string_view(logger::severity s)
{
    constexpr std::string_view strs[] =
        { "TRACE", "DEBUG", "INFO", "NOTICE", "WARNING", "ERROR", "FATAL" };
    return strs[static_cast<int>(s)];
}
#endif
//----------------------------------------------------------------------------

} // namespace

#endif // header guard
