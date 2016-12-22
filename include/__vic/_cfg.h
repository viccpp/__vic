// Internal header. Config for current compiler/processor/OS
//
// Hardware platforms (CPU):
// __VIC_X86__      - Intel x86 (IA32)
// __VIC_X64__      - x64 AKA x86-64 AKA AMD 64
// __VIC_IA64__     - Intel IA64
// __VIC_SPARC32__  - Sun SPARC 32-bit
// __VIC_SPARC64__  - Sun SPARC 64-bit
// __VIC_POWERPC__  - PowerPC
//
// Software platforms (OS):
// __VIC_LINUX__    - Linux
// __VIC_FREEBSD__  - FreeBSD
// __VIC_QNX__      - QNX Neutrino
// __VIC_SUNOS__    - Solaris
// __VIC_HPUX__     - HP-UX
// __VIC_AIX__      - AIX
// __VIC_WINDOWS__  - Windows
//
// Other defines:
// __VIC_STRICT_RAM_ALIGNMENT__ - unaligned data cannot be fetched from RAM
//
// $Id$
//
// (c) __vic 2007

#ifndef __VIC__CFG_H
#define __VIC__CFG_H

//////////////////////////////////////////////////////////////////////////////
// Clang 3.4 or higher
//////////////////////////////////////////////////////////////////////////////
#if defined(__clang__) && (__clang_major__ > 3 || \
    __clang_major__ == 3 && __clang_minor__ >= 4)

//////////////////////////////////////////////////////////////////////////////
// GNU C++ 5 or higher
//////////////////////////////////////////////////////////////////////////////
#elif defined(__GNUC__) && __GNUC__ >= 5

#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1 // use all
#endif

#if defined(__GXX_EXPERIMENTAL_CXX0X__) && !defined(__VIC_NO_NULLPTR_DEF)
#define __VIC_NO_NULLPTR_DEF 1
#endif

// GCC bug: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=71214
#if !__cpp_rvalue_references && __cpp_rvalue_reference
#define __cpp_rvalue_references __cpp_rvalue_reference
#endif

//////////////////////////////////////////////////////////////////////////////
// Compiler is not recognized
//////////////////////////////////////////////////////////////////////////////
#else
#error Unsupported compiler
#endif // compilers

//////////////////////////////////////////////////////////////////////////////
// Detect CPU type
#if defined(__GNUC__) || defined(__clang__)

#if defined(__i386__)
#define __VIC_X86__ 1
#define __VIC_CPU_DEFINED 1
#elif defined(__x86_64__) || defined(__amd64__)
#define __VIC_X64__ 1
#define __VIC_CPU_DEFINED 1
#elif defined(__IA64__)
#define __VIC_IA64__ 1
#define __VIC_CPU_DEFINED 1
#elif defined(_POWER) || defined(__PPC__)
#define __VIC_POWERPC__ 1
#define __VIC_CPU_DEFINED 1
#endif

#elif defined(_MSC_VER)

#if defined(_M_X86)
#define __VIC_X86__ 1
#define __VIC_CPU_DEFINED 1
#elif defined(_M_X64) || defined(_M_AMD64)
#define __VIC_X64__ 1
#define __VIC_CPU_DEFINED 1
#endif

#endif // compiler

#ifndef __VIC_CPU_DEFINED
#error Unsupported processor
#endif
#undef __VIC_CPU_DEFINED
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Detect OS
#if defined(__linux__)
#define __VIC_LINUX__ 1
#elif defined(__FreeBSD__)
#define __VIC_FREEBSD__ 1
#elif defined(_WIN32) // MinGW
#define __VIC_WINDOWS__ 1
#elif defined(_AIX)
#define __VIC_AIX__ 1
#elif defined(__sun)
#define __VIC_SUNOS__
#elif defined(__QNX__)
#define __VIC_QNX__
#elif defined(__hpux)
#define __VIC_HPUX__ 1
#else
#error Unsupported OS
#endif
//////////////////////////////////////////////////////////////////////////////

#if !(defined(__VIC_X86__) || defined(__VIC_X64__))
// Memory access to unaligned data will cause bus error
#define __VIC_STRICT_RAM_ALIGNMENT__ 1
#endif

// Always use Large File Support for Linux-x86
#if defined(__linux__) && defined(__VIC_X86__) && \
    !defined(__VIC_NO_LARGE_FILE_SUPPORT)
#define _FILE_OFFSET_BITS 64
#endif

//////////////////////////////////////////////////////////////////////////////
// C++14/C++11/C++98 compatibility macros
#if __cplusplus < 201103L && !defined(__VIC_NO_NOEXCEPT_DEF)
#define noexcept throw()
#endif

#if defined(_MSC_VER) && _MSC_VER < 0x1400
#define __VIC_LONGLONG __int64
#else
#define __VIC_LONGLONG long long
#endif

#if __cplusplus >= 201103L // C++11
#   define __VIC_THROWS noexcept(false)
#   define __VIC_CONSTEXPR_FUNC constexpr
#   define __VIC_CONSTEXPR_VAR constexpr
#   define __VIC_DEFAULT_CTR =default;
#   if defined(__GNUC__) && __GNUC__ < 5
#       define __VIC_CXX11_CONST_ITERATOR iterator
#   else
#       define __VIC_CXX11_CONST_ITERATOR const_iterator
#   endif
#   define __VIC_SWAP_HEADER <algorithm>
#   define __VIC_NORETURN [[noreturn]]
#else // C++98
#   define __VIC_THROWS
#   define __VIC_CONSTEXPR_FUNC inline
#   define __VIC_CONSTEXPR_VAR const
#   define __VIC_DEFAULT_CTR {}
#   define __VIC_CXX11_CONST_ITERATOR iterator
#   define __VIC_SWAP_HEADER <utility>
#   if defined(__GNUC__) || defined(__clang__)
#       define __VIC_NORETURN __attribute__((noreturn))
#   elif defined(_MSC_VER)
#       define __VIC_NORETURN __declspec(noreturn)
#   else
#       define __VIC_NORETURN
#   endif
#endif
//////////////////////////////////////////////////////////////////////////////

#endif // header guard
