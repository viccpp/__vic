//
// $Id$
//

#include<__vic/utf8/defs.h>
#include<cassert>

namespace __vic { namespace utf8 {

//----------------------------------------------------------------------------
// Minimal amount of bytes needed to encode the code point
extern const unicode_t length_thresholds[5] =
// bytes:   2     3      4        5         6
        { 0x80, 0x800, 0x10000, 0x200000, 0x4000000 };
//----------------------------------------------------------------------------

}} // namespace
