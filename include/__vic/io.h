// I/O utilities
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2007

#ifndef __VIC_IO_H
#define __VIC_IO_H

#include<__vic/defs.h>
#include __VIC_SWAP_HEADER
#include<cstdio>
#include<string>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
// FILE * wrapper
//////////////////////////////////////////////////////////////////////////////
class stdio_file : private non_copyable
{
    std::FILE *fp;
public:
    explicit stdio_file(std::FILE *fp = nullptr) : fp(fp) {}
    stdio_file(const char *name, const char *mode) { open(name, mode); }
    ~stdio_file() { if(is_open()) std::fclose(fp); }

#if __cpp_rvalue_references
    stdio_file(stdio_file &&o) noexcept : fp(o.fp) { o.fp = nullptr; }
    stdio_file &operator=(stdio_file &&o) noexcept { swap(o); return *this; }
#endif

    bool open(const char *name, const char *mode)
        { return (fp = std::fopen(name, mode)); }
    void close();
    bool is_open() const { return fp; }
    bool close_nt() noexcept
        { int st = std::fclose(fp); fp = nullptr; return st == 0; }
    std::FILE *detach() { std::FILE *f = fp; fp = nullptr; return f; }
    void attach(std::FILE *f) { fp = f; }
    void swap(stdio_file &o) noexcept { std::swap(fp, o.fp); }
    operator std::FILE*() const { return fp; }
};
//////////////////////////////////////////////////////////////////////////////

__VIC_NORETURN void throw_stdio_read_error();
__VIC_NORETURN void throw_stdio_write_error();
//----------------------------------------------------------------------------
inline bool read(std::FILE *fp, char &ch)
{
    using namespace std; // cannot write "std::getc" if getc is a macro
    int c = getc(fp);
    if(c == EOF)
    {
        if(ferror(fp)) throw_stdio_read_error();
        return false; // feof(fp)
    }
    ch = c;
    return true;
}
//----------------------------------------------------------------------------
inline void write(std::FILE *fp, char ch)
{
    using namespace std; // cannot write "std::putc" if putc is a macro
    if(putc(ch, fp) == EOF) throw_stdio_write_error();
}
//----------------------------------------------------------------------------

// Read std::string from C-stream
bool getline(std::FILE * , std::string & , char = '\n');

//////////////////////////////////////////////////////////////////////////////
// Reader<char>
class cstream_reader
{
    std::FILE *fp;
public:
    explicit cstream_reader(std::FILE *fp) : fp(fp) {}
    bool read(char &ch) { return __vic::read(fp, ch); }
};
//////////////////////////////////////////////////////////////////////////////
// Writer<char>
class cstream_writer
{
    std::FILE *fp;
public:
    explicit cstream_writer(std::FILE *fp) : fp(fp) {}
    void write(char ch) { __vic::write(fp, ch); }
};
//////////////////////////////////////////////////////////////////////////////

} // namespace

#endif // header guard
