//
// $Id$
//

#include<__vic/windows/wchar.h>
#include<__vic/utf16/reader.h>
#include<__vic/utf8/writer.h>
#include<__vic/readers/iterator.h>
#include<__vic/writers/string.h>
#include<__vic/unicode.h>

namespace __vic { namespace windows {

namespace {
//////////////////////////////////////////////////////////////////////////////
class wchar_reader
{
    iterator_reader_n<const utf16::code_unit_t *> r;
public:
    wchar_reader(const wchar_t *s, size_t n)
        : r(reinterpret_cast<const utf16::code_unit_t *>(s), n) {}

    utf16::status_t read_unit(utf16::code_unit_t &u)
    {
        return r.read(u) ? utf16::status::ok : utf16::status::eof;
    }
};
//////////////////////////////////////////////////////////////////////////////
} // namespace
//----------------------------------------------------------------------------
std::string utf16to8(const wchar_t *s, size_t len_in_code_points)
{
    std::string res; res.reserve(len_in_code_points);
    utf_transcode(
        __vic::utf16::make_reader(wchar_reader(s, len_in_code_points)),
        __vic::utf8::make_writer(__vic::make_string_writer(res))
    );
    return res;
}
//----------------------------------------------------------------------------

}} // namespace
