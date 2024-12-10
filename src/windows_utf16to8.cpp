//
// $Id$
//

#include<__vic/windows/wchar.h>
#include<__vic/utf16/reader.h>
#include<__vic/utf8/writer.h>
#include<__vic/sreaders/iterator.h>
#include<__vic/swriters/string.h>
#include<__vic/unicode.h>

namespace __vic { namespace windows {

namespace {
//////////////////////////////////////////////////////////////////////////////
class wchar_reader
{
    iterator_sreader_n<const utf16::code_unit_t *> r;
public:
    wchar_reader(const wchar_t *s, size_t n)
        : r(reinterpret_cast<const utf16::code_unit_t *>(s), n) {}

    utf16::read_unit_result operator()()
    {
        if(__vic::sread_result<__vic::utf16::code_unit_t> u = r())
            return u.value();
        return __vic::utf16::status::eof;
    }
};
//////////////////////////////////////////////////////////////////////////////
} // namespace
//----------------------------------------------------------------------------
std::string &utf16to8_append(const wchar_t *s, size_t len, std::string &res)
{
    utf_transcode(
        utf16::make_reader(wchar_reader(s, len)),
        utf8::make_writer(make_string_swriter(res))
    );
    return res;
}
//----------------------------------------------------------------------------
std::string utf16to8(const wchar_t *s, size_t len)
{
    std::string res; res.reserve(len);
    utf16to8_append(s, len, res);
    return res;
}
//----------------------------------------------------------------------------

}} // namespace
