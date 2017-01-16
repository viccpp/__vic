// Bits/bytes manipulation tools
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_BITS_H
#define __VIC_BITS_H

#include<__vic/defs.h>
#include<__vic/stdint.h>
#include<climits>

namespace __vic {

//----------------------------------------------------------------------------
// Returns low-order nibble (or tetrad, or half-byte) of the byte
__VIC_CONSTEXPR_FUNC int lo_nibble(uint8_t b)
{
    return b & 0x0F;
}
//----------------------------------------------------------------------------
// Returns high-order nibble (or tetrad, or half-byte) of the byte
__VIC_CONSTEXPR_FUNC int hi_nibble(uint8_t b)
{
    return b >> 4;
}
//------------------------------------------------------------------------------
// Returns value with all most significant bits are 1 (others - 0)
// Parameter specifies the number of "ones"
template<class T>
inline T msb_ones(unsigned bits_num)
{
    return ~T(0) << (sizeof(T) * CHAR_BIT - bits_num);
}
//------------------------------------------------------------------------------
// Returns value with all least significant bits are 1 (others - 0)
// Parameter specifies the number of "ones"
template<class T>
inline T lsb_ones(unsigned bits_num)
{
    return ~(~T(0) << bits_num);
}
//------------------------------------------------------------------------------
// Clears all but bits_num least significant bits
template<class T>
inline T get_lsbs(T v, unsigned bits_num)
{
    return v & lsb_ones<T>(bits_num);
}
//----------------------------------------------------------------------------
// Returns char code 0..255
__VIC_CONSTEXPR_FUNC int ord(char ch)
{
    return static_cast<unsigned char>(ch);
}
//----------------------------------------------------------------------------
__VIC_CONSTEXPR_FUNC char to_hex_digit_upper(int tetrad)
{
    // assert(0 <= tetrad && tetrad <= 15);
    return tetrad < 10 ? tetrad + '0' : tetrad - 10 + 'A';
}
//----------------------------------------------------------------------------
__VIC_CONSTEXPR_FUNC char to_hex_digit_lower(int tetrad)
{
    // assert(0 <= tetrad && tetrad <= 15);
    return tetrad < 10 ? tetrad + '0' : tetrad - 10 + 'a';
}
//----------------------------------------------------------------------------
// Convert HEX-digit to integer number
// Returns -1 on error
__VIC_CONSTEXPR_FUNC int hex_to_number(char ch)
{
    return '0' <= ch && ch <= '9' ? ch - '0' :
           'A' <= ch && ch <= 'F' ? ch - 'A' + 10 :
           'a' <= ch && ch <= 'f' ? ch - 'a' + 10 :
           -1; // Not a hex digit
}
//----------------------------------------------------------------------------
// Swap high-order nibble with low-order one
__VIC_CONSTEXPR_FUNC uint8_t swapped_nibbles(uint8_t b)
{
    return (b << 4) | (b >> 4);
}
//----------------------------------------------------------------------------
template<class UInt>
inline UInt rotl_uint(UInt v, int shift)
{
    return (v << shift) | (v >> (sizeof(UInt) * CHAR_BIT - shift));
}
//----------------------------------------------------------------------------
template<class UInt>
inline UInt rotr_uint(UInt v, int shift)
{
    return (v >> shift) | (v << (sizeof(UInt) * CHAR_BIT - shift));
}
//----------------------------------------------------------------------------
inline uint8_t  rotl(uint8_t  v, int sh) { return rotl_uint(v, sh); }
inline uint16_t rotl(uint16_t v, int sh) { return rotl_uint(v, sh); }
inline uint32_t rotl(uint32_t v, int sh) { return rotl_uint(v, sh); }
inline uint64_t rotl(uint64_t v, int sh) { return rotl_uint(v, sh); }
//----------------------------------------------------------------------------
inline uint8_t  rotr(uint8_t  v, int sh) { return rotr_uint(v, sh); }
inline uint16_t rotr(uint16_t v, int sh) { return rotr_uint(v, sh); }
inline uint32_t rotr(uint32_t v, int sh) { return rotr_uint(v, sh); }
inline uint64_t rotr(uint64_t v, int sh) { return rotr_uint(v, sh); }
//----------------------------------------------------------------------------

} // namespace

#endif // header guard
