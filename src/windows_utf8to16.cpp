//
// $Id$
//

#include<__vic/windows/wchar.h>
#include<__vic/utf8/reader.h>
#include<__vic/utf16/writer.h>
#include<__vic/sreaders/iterator.h>
#include<__vic/swriters/string.h>
#include<__vic/unicode.h>

namespace __vic { namespace windows {

//----------------------------------------------------------------------------
wstring utf8to16(const char *s, size_t len)
{
    wstring res(len * 2);
    utf_transcode(
        utf8::make_reader(make_iterator_sreader_n_for<unsigned char>(s, len)),
        utf16::make_writer(make_string_swriter(res))
    );
    return res;
}
//----------------------------------------------------------------------------

}} // namespace
