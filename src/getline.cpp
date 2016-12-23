//
// $Id$
//

#include<__vic/io.h>
#include<__vic/error.h>

namespace __vic {

namespace {
//----------------------------------------------------------------------------
inline bool read_char(std::FILE *fp, char &ch)
{
    using namespace std; // cannot write "std::getc" if getc is macro
    int c = getc(fp);
    if(c == EOF)
    {
        if(ferror(fp)) throw exception("I/O error: read failed");
        return false; // feof(fp)
    }
    ch = c;
    return true;
}
//----------------------------------------------------------------------------
}
//----------------------------------------------------------------------------
bool getline(std::FILE *fp, std::string &buf, char delim)
{
    char ch;
    if(!read_char(fp, ch)) return false; // end-of-file
    buf.clear();
    do {
        if(ch == delim) break;
        buf.push_back(ch);
    } while(read_char(fp, ch));
    return true;
}
//----------------------------------------------------------------------------

} // namespace
