//
// $Id$
//

#include<__vic/windows/wchar.h>
#include<__vic/utf8/reader.h>
#include<__vic/utf16/writer.h>
#include<__vic/readers/iterator.h>
#include<__vic/writers/string.h>
#include<__vic/unicode.h>

namespace __vic { namespace windows {

//----------------------------------------------------------------------------
wstring utf8to16(const char *s, size_t len)
{
    wstring res(len * 2);

    typedef iterator_reader_n<const unsigned char *> char_reader;
    char_reader char_rd(reinterpret_cast<const unsigned char *>(s), len);
    utf8::reader<char_reader> r(char_rd);

    typedef basic_string_writer<wchar_t> wchar_writer;
    wchar_writer wchar_wr(res);
    utf16::writer<wchar_writer> w(wchar_wr);

    unicode_t cp;
    while(r.read(cp)) w.write(cp);
    return res;
}
//----------------------------------------------------------------------------

}} // namespace
