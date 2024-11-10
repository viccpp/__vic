//
// $Id$
//

#include<__vic/stdio_file.h>

namespace __vic {

//----------------------------------------------------------------------------
bool getline(std::FILE *fp, std::string &buf, char delim)
{
    sread_result<char> ch = read(fp);
    if(!ch) return false; // end-of-file
    buf.clear();
    do {
        if(ch.value() == delim) break;
        buf.push_back(ch.value());
    } while((ch = read(fp)));
    return true;
}
//----------------------------------------------------------------------------

} // namespace
