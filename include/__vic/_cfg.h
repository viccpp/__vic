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
// Visual C++ 7.1 (Visual Studio 2003) or higher
//////////////////////////////////////////////////////////////////////////////
#elif defined(_MSC_VER) && _MSC_VER >= 1310

// VC++ features: https://msdn.microsoft.com/en-us/library/hh567368.aspx
#if _MSC_VER >= 1600 // VC 10.0 (VS 2010)

#define __VIC_NO_NULLPTR_DEF 1
#if !__cpp_rvalue_references
#   define __cpp_rvalue_references 1
#endif
#if !__cpp_lambdas
#   define __cpp_lambdas 1
#endif
#if !__cpp_static_assert
#   define __cpp_static_assert 1
#endif

#if _MSC_VER >= 1800 // VC 12.0 (VS 2013)

#if !__cpp_initializer_lists
#   define __cpp_initializer_lists 1
#endif
#if !__cpp_alias_templates
#   define __cpp_alias_templates 1
#endif
#if !__cpp_variadic_templates
#   define __cpp_variadic_templates 1
#endif

#if _MSC_VER >= 1900 // VS 14.0 (2015)
#define __VIC_NO_NOEXCEPT_DEF 1
#if !__cpp_constexpr
#   define __cpp_constexpr 1
#endif
#if !__cpp_attributes
#   define __cpp_attributes 1
#endif
#endif // VS 2015

#endif // VS 2013

#endif // VS 2010

//////////////////////////////////////////////////////////////////////////////
// Compiler is not recognized
//////////////////////////////////////////////////////////////////////////////
#else
#error Unsupported compiler
#endif // compilers

//////////////////////////////////////////////////////////////////////////////
// Detect CPU type
//////////////////////////////////////////////////////////////////////////////
#if defined(__GNUC__) || defined(__clang__)

// x64 should be checked first because somtimes x86 macros are defined too
#if defined(__x86_64__) || defined(__amd64__)
#define __VIC_X64__ 1
#define __VIC_CPU_DEFINED 1
#elif defined(__i386__)
#define __VIC_X86__ 1
#define __VIC_CPU_DEFINED 1
#elif defined(__IA64__)
#define __VIC_IA64__ 1
#define __VIC_CPU_DEFINED 1
#elif defined(_POWER) || defined(__PPC__)
#define __VIC_POWERPC__ 1
#define __VIC_CPU_DEFINED 1
#endif

#elif defined(_MSC_VER)

#if defined(_M_X64) || defined(_M_AMD64)
#define __VIC_X64__ 1
#define __VIC_CPU_DEFINED 1
#elif defined(_M_IX86)
#define __VIC_X86__ 1
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
//////////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////////
#if __cplusplus < 201103L && !defined(__VIC_NO_NOEXCEPT_DEF)
#define noexcept throw()
#endif

#if defined(_MSC_VER) && _MSC_VER < 0x1400 // VC 8.0 (VS 2005)
#define __VIC_LONGLONG __int64
#define __VIC_PRINTF_ll "I64"
#else
#define __VIC_LONGLONG long long
#define __VIC_PRINTF_ll "ll"
#endif

#if __cplusplus >= 201103L // C++11
#   if !__cpp_constexpr
#       define __cpp_constexpr 1
#   endif
#   if !__cpp_attributes
#       define __cpp_attributes 1
#   endif
#   define __VIC_THROWS noexcept(false)
#   define __VIC_DEFAULT_CTR =default;
#   if defined(__GNUC__) && __GNUC__ < 5
#       define __VIC_CXX11_CONST_ITERATOR iterator
#   else
#       define __VIC_CXX11_CONST_ITERATOR const_iterator
#   endif
#   define __VIC_SWAP_HEADER <algorithm>
#else // C++98
#   define __VIC_THROWS
#   define __VIC_DEFAULT_CTR {}
#   define __VIC_CXX11_CONST_ITERATOR iterator
#   define __VIC_SWAP_HEADER <utility>
#endif

#if __cpp_constexpr
#   define __VIC_CONSTEXPR_FUNC constexpr
#   define __VIC_CONSTEXPR_VAR constexpr
#else
#   define __VIC_CONSTEXPR_FUNC inline
#   define __VIC_CONSTEXPR_VAR const
#endif

#if __cpp_attributes
#   define __VIC_NORETURN [[noreturn]]
#else
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
