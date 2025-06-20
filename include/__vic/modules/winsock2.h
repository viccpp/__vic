// "Fixed" <winsock2.h> header usable with C++ modules
//
// $Id$

#ifndef __VIC_MODULES_WINSOCK2_H
#define __VIC_MODULES_WINSOCK2_H

#ifdef __GNUC__
extern "C++" {
#include<pmmintrin.h>
}
#endif

#include<winsock2.h> // must be included before windows.h
#include<windows.h>

#endif // header guard
