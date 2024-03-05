// Logger front-end
//
// Platform: ISO C++ 98/11/17/20
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
#if __has_include(<format>)
#include<format>
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

#if __cpp_lib_format >= 202106L // C++20 + P2508
private:
    void vformat_(severity_t , std::string_view , std::format_args );
public:
    template<class... Args>
    void format(severity_t s, std::format_string<Args...> fmt, Args&&... args)
    {
        if(s >= level())
            vformat_(s, fmt.get(), std::make_format_args(args...));
    }

    template<class Arg1, class... Args>
    void trace(
        std::format_string<Arg1,Args...> fmt, Arg1 &&arg1, Args&&... args)
    {
        format(severity::trace, fmt,
                std::forward<Arg1>(arg1), std::forward<Args>(args)...);
    }
    template<class Arg1, class... Args>
    void debug(
        std::format_string<Arg1,Args...> fmt, Arg1 &&arg1, Args&&... args)
    {
        format(severity::debug, fmt,
                std::forward<Arg1>(arg1), std::forward<Args>(args)...);
    }
    template<class Arg1, class... Args>
    void info(
        std::format_string<Arg1,Args...> fmt, Arg1 &&arg1, Args&&... args)
    {
        format(severity::info, fmt,
                std::forward<Arg1>(arg1), std::forward<Args>(args)...);
    }
    template<class Arg1, class... Args>
    void notice(
        std::format_string<Arg1,Args...> fmt, Arg1 &&arg1, Args&&... args)
    {
        format(severity::notice, fmt,
                std::forward<Arg1>(arg1), std::forward<Args>(args)...);
    }
    template<class Arg1, class... Args>
    void warning(
        std::format_string<Arg1,Args...> fmt, Arg1 &&arg1, Args&&... args)
    {
        format(severity::warning, fmt,
                std::forward<Arg1>(arg1), std::forward<Args>(args)...);
    }
    template<class Arg1, class... Args>
    void error(
        std::format_string<Arg1,Args...> fmt, Arg1 &&arg1, Args&&... args)
    {
        format(severity::error, fmt,
                std::forward<Arg1>(arg1), std::forward<Args>(args)...);
    }
    template<class Arg1, class... Args>
    void fatal(
        std::format_string<Arg1,Args...> fmt, Arg1 &&arg1, Args&&... args)
    {
        format(severity::fatal, fmt,
                std::forward<Arg1>(arg1), std::forward<Args>(args)...);
    }
#endif

    bool trace_visible() const { return level() <= severity::trace; }
    bool debug_visible() const { return level() <= severity::debug; }
    bool info_visible() const { return level() <= severity::info; }
    bool notice_visible() const { return level() <= severity::notice; }
    bool warning_visible() const { return level() <= severity::warning; }
    bool error_visible() const { return level() <= severity::error; }
    bool fatal_visible() const { return level() <= severity::fatal; }
private:
    output *out;
    //severity log_level; // moved to make the struct more compact

    // current record buffer
    string_buffer cur_msg;
    size_t rec_objs_count;
    severity_t cur_severity;

    severity_t log_level;

    void flush_();
    void inc_count_() { rec_objs_count++; }
    void dec_count_() { if(--rec_objs_count == 0) flush_(); }
};
//////////////////////////////////////////////////////////////////////////////
class logger::record
{
    logger &log;
public:
    record(logger &log, severity_t severity) : log(log)
    {
        log.cur_severity = severity;
        log.inc_count_();
    }
    record(const record &o) : log(o.log) { log.inc_count_(); }
    ~record() { log.dec_count_(); }

    record append(const char *s, size_t n)
        { log.cur_msg.append(s, n); return *this; }

    template<class T>
    record operator<<(const T &v) { log.cur_msg << v; return *this; }
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
