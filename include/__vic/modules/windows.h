// "Fixed" <windows.h> header usable with C++ modules
//
// $Id$

#ifndef __VIC_MODULES_WINDOWS_H
#define __VIC_MODULES_WINDOWS_H

#ifdef __GNUC__
extern "C++" {
#include<pmmintrin.h>
}
#endif

#include<windows.h>

#endif // header guard
