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
// __linux__    - Linux
// __FreeBSD__  - FreeBSD
// __QNX__      - QNX Neutrino
// __sun        - Solaris
// __hpux       - HP-UX
// _AIX         - AIX
// _WIN32       - Windows
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
// Intel C++ 17.0 or higher
//////////////////////////////////////////////////////////////////////////////
#elif defined(__INTEL_COMPILER) && __INTEL_COMPILER >= 1700

//////////////////////////////////////////////////////////////////////////////
// GNU C++ 4.7 or higher
//////////////////////////////////////////////////////////////////////////////
#elif defined(__GNUC__) && (__GNUC__ > 4 || __GNUC__ == 4 && __GNUC_MINOR__ >= 7)

#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1 // use all
#endif

#if defined(__GXX_EXPERIMENTAL_CXX0X__) && !defined(__VIC_NO_NULLPTR_DEF)
#define __VIC_NO_NULLPTR_DEF 1
#endif

// Define SD-6 feature test macros for old versions
#if __GNUC__ < 5 && __cplusplus >= 201103L
// __cplusplus has been correctly defined only since 4.7
#ifndef __cpp_rvalue_references
#define __cpp_rvalue_references 200610
#endif
#ifndef __cpp_variadic_templates
#define __cpp_variadic_templates 200704
#endif
#ifndef __cpp_initializer_lists
#define __cpp_initializer_lists 200806
#endif
#ifndef __cpp_static_assert
#define __cpp_static_assert 200410
#endif
#ifndef __cpp_lambdas
#define __cpp_lambdas 200907
#endif
#ifndef __cpp_decltype
#define __cpp_decltype 200707
#endif
#ifndef __cpp_constexpr
#define __cpp_constexpr 200704
#endif
#ifndef __cpp_unicode_characters
#define __cpp_unicode_characters 200704
#endif
#ifndef __cpp_unicode_literals
#define __cpp_unicode_literals 200710
#endif
#ifndef __cpp_raw_strings
#define __cpp_raw_strings 200710
#endif
#ifndef __cpp_range_based_for
#define __cpp_range_based_for 200907
#endif
#ifndef __cpp_threadsafe_static_init
#define __cpp_threadsafe_static_init 200806
#endif
#ifndef __cpp_nsdmi
#define __cpp_nsdmi 200809
#endif
#ifndef __cpp_alias_templates
#define __cpp_alias_templates 200704
#endif
#ifndef __cpp_delegating_constructors
#define __cpp_delegating_constructors 200604
#endif
#ifndef __cpp_user_defined_literals
#define __cpp_user_defined_literals 200809
#endif
#if __GNUC_MINOR__ >= 8 // 4.8
#ifndef __cpp_attributes
#define __cpp_attributes 200809
#endif
#ifndef __cpp_inheriting_constructors
#define __cpp_inheriting_constructors 200802
#endif
#if __GNUC_PATCHLEVEL__ >= 1 // 4.8.1
#ifndef __cpp_ref_qualifiers
#define __cpp_ref_qualifiers 200710
#endif
#endif // 4.8.1
#endif // 4.8
#endif // SD-6

// GCC bug: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=71214
#if !defined(__cpp_rvalue_references) && defined(__cpp_rvalue_reference)
#define __cpp_rvalue_references __cpp_rvalue_reference
#endif

//////////////////////////////////////////////////////////////////////////////
// Visual C++ 7.1 (Visual Studio 2003) or higher
//////////////////////////////////////////////////////////////////////////////
#elif defined(_MSC_VER) && _MSC_VER >= 1310

// VC++ features: https://msdn.microsoft.com/en-us/library/hh567368.aspx
// VC 15.8 (VS 2017) is the first version that implements feature-test macros
#if _MSC_VER < 1915 && _MSC_VER >= 1600 // VC 10.0 (VS 2010)

#define __VIC_NO_NULLPTR_DEF 1
#ifndef __cpp_rvalue_references
#define __cpp_rvalue_references 1
#endif
#ifndef __cpp_lambdas
#define __cpp_lambdas 1
#endif
#ifndef __cpp_static_assert
#define __cpp_static_assert 1
#endif

#if _MSC_VER >= 1800 // VC 12.0 (VS 2013)

#ifndef __cpp_initializer_lists
#define __cpp_initializer_lists 1
#endif
#ifndef __cpp_alias_templates
#define __cpp_alias_templates 1
#endif
#ifndef __cpp_variadic_templates
#define __cpp_variadic_templates 1
#endif

#if _MSC_VER >= 1900 // VC 14.0 (2015)
#define __VIC_NO_NOEXCEPT_DEF 1
#ifndef __cpp_constexpr
#define __cpp_constexpr 1
#endif
#ifndef __cpp_attributes
#define __cpp_attributes 1
#endif
#ifndef __cpp_unicode_characters
#define __cpp_unicode_characters 1
#endif
#endif // VS 2015

#endif // VS 2013

#endif // VS 2010-2017

//////////////////////////////////////////////////////////////////////////////
// Compiler is not recognized
//////////////////////////////////////////////////////////////////////////////
#else
#error Unsupported compiler
#endif // compilers

//////////////////////////////////////////////////////////////////////////////
// Detect CPU type
//////////////////////////////////////////////////////////////////////////////
#if defined(__GNUC__) || defined(__clang__) || defined(__INTEL_COMPILER)

// x64 should be checked first because sometimes x86 macros are defined too
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
#   define __VIC_THROWS noexcept(false)
#   define __VIC_SWAP_HEADER <algorithm>
#   define __VIC_SCOPED_ENUM_UT_BEGIN(name,type) enum class name : type
#   define __VIC_SCOPED_ENUM_BEGIN(name) enum class name
#   define __VIC_SCOPED_ENUM_END(name) ; using name##_t = name;
#else // C++98
#   define __VIC_THROWS
#   define __VIC_SWAP_HEADER <utility>
#   define __VIC_SCOPED_ENUM_UT_BEGIN(name,type) struct name { enum type_
#   define __VIC_SCOPED_ENUM_BEGIN(name) struct name { enum type_
#   define __VIC_SCOPED_ENUM_END(name) ; }; typedef name::type_ name##_t;
#endif

#if __cpp_rvalue_references
#   define __VIC_STD_MOVE(v) std::move(v)
#else
#   define __VIC_STD_MOVE(v) v
#endif

#if __cpp_constexpr
#   define __VIC_CONSTEXPR_FUNC constexpr
#   define __VIC_CONSTEXPR_VAR constexpr
#   define __VIC_DEFAULT_CTR =default;
#else
#   define __VIC_CONSTEXPR_FUNC inline
#   define __VIC_CONSTEXPR_VAR const
#   define __VIC_DEFAULT_CTR {}
#endif

#if __cpp_constexpr >= 201304
#   define __VIC_CONSTEXPR14 constexpr
#else
#   define __VIC_CONSTEXPR14 inline
#endif

#if __cpp_if_consteval
#   define __VIC_IF_CONSTEVAL if consteval
#   define __VIC_IF_NOT_CONSTEVAL if !consteval
#else
#   define __VIC_IF_CONSTEVAL if(std::is_constant_evaluated())
#   define __VIC_IF_NOT_CONSTEVAL if(!std::is_constant_evaluated())
#endif

#ifndef __has_include
#   define __has_include(f) 0
#endif

#ifndef __has_cpp_attribute
#   define __has_cpp_attribute(a) 0
#endif

#if __cpp_attributes && __has_cpp_attribute(nodiscard) && \
    !defined(__clang__)
// Clang 3.9+ issue - https://bugs.llvm.org/show_bug.cgi?id=33518
#   define __VIC_NODISCARD [[nodiscard]]
#else
#   define __VIC_NODISCARD
#endif

#if __cpp_attributes
#   define __VIC_NORETURN [[noreturn]]
#else
#   if defined(__GNUC__)
#       define __VIC_NORETURN __attribute__((noreturn))
#   elif defined(_MSC_VER)
#       define __VIC_NORETURN __declspec(noreturn)
#   else
#       define __VIC_NORETURN
#   endif
#endif
//////////////////////////////////////////////////////////////////////////////

#endif // header guard
