// String utilities
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2007

#ifndef __VIC_STRING_OPS_H
#define __VIC_STRING_OPS_H

#include<__vic/defs.h>
#include<__vic/readers.h>
#include<__vic/writers.h>
#include<algorithm>
#include<string>

namespace __vic {

typedef container_reader<std::string> string_reader;
typedef push_back_writer<std::string> string_writer;

//----------------------------------------------------------------------------
char *trim(char * ) noexcept;
char *trim_left(char * ) noexcept;
char *trim_right(char * ) noexcept;
char *trim(char * , char ) noexcept;
char *trim_left(char * , char ) noexcept;
char *trim_right(char * , char ) noexcept;
char *trim(char * , const char * ) noexcept;
char *trim_left(char * , const char * ) noexcept;
char *trim_right(char * , const char * ) noexcept;
//----------------------------------------------------------------------------
std::string &trim(std::string & );
std::string &trim_left(std::string & );
std::string &trim_right(std::string & );
std::string &trim(std::string & , char );
std::string &trim_left(std::string & , char );
std::string &trim_right(std::string & , char );
std::string &trim(std::string & , const char * );
std::string &trim_left(std::string & , const char * );
std::string &trim_right(std::string & , const char * );
//----------------------------------------------------------------------------
std::string trimmed(const std::string & );
std::string trimmed_left(const std::string & );
std::string trimmed_right(const std::string & );
std::string trimmed(const std::string & , char );
std::string trimmed_left(const std::string & , char );
std::string trimmed_right(const std::string & , char );
std::string trimmed(const std::string & , const char * );
std::string trimmed_left(const std::string & , const char * );
std::string trimmed_right(const std::string & , const char * );
//----------------------------------------------------------------------------

namespace impl {
//----------------------------------------------------------------------------
template<class Pred>
inline char *sift_if(char *st, Pred pred)
{
    if(!st) return st;
    char *in = st;
    while(*in && !pred(*in)) in++;
    if(!*in) return st; // no trash chars
    char *out = in;
    do {
        in++;
        if(!pred(*in)) *out++ = *in;
    } while(*in);
    *out = '\0';
    return st;
}
//----------------------------------------------------------------------------
template<class Pred>
std::string &sift_if(std::string &st, Pred pred)
{
    std::string::iterator in = st.begin();
    while(in != st.end() && !pred(*in)) ++in;
    if(in == st.end()) return st; // no trash chars
    std::string::iterator out = in;
    do {
        ++in;
        if(!pred(*in)) *out++ = *in;
    } while(in != st.end());
    st.erase(out, st.end());
    return st;
}
//----------------------------------------------------------------------------
} // namespace

//----------------------------------------------------------------------------
char *sift(char * , const char * );
std::string &sift(std::string & , const char * );

template<class Pred>
char *sift_if(char *s, Pred pred) { return impl::sift_if(s, pred); }

template<class Pred>
std::string &sift_if(std::string &s, Pred pred) { return impl::sift_if(s, pred);}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
std::string &pad_left(std::string & , size_t , char = ' ');
std::string &pad_right(std::string & , size_t , char = ' ');
char *pad_left(char * , size_t , char = ' ');
char *pad_right(char * , size_t , char = ' ');
//----------------------------------------------------------------------------

} // namespace

#endif // header guard
