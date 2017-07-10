#pragma once

// OS (defaults to UNIX if can't determine others)
#define ALIGN_OS_WIN 1
#define ALIGN_OS_MAC 2
#define ALIGN_OS_UNIX 4

// Compiler (currently doesn't detect GCC)
#define ALIGN_CC_MSVC 1
#define ALIGN_CC_CLANG 2
#define ALIGN_CC_GCC 4
#define ALIGN_CC_MSVC7 8

// Processor
#define ALIGN_PROC_x86 1
#define ALIGN_PROC_POWERPC 2
#define ALIGN_PROC_x64 4
//#define ALIGN_PROC_IA64 8
//#define ALIGN_PROC_MIPS 16
//#define ALIGN_PROC_SPARC 32

// Endian-ness
#define ALIGN_ENDIAN_BIG 1
#define ALIGN_ENDIAN_LITTLE 2

//Auto-detect macros below
//Detect OS
#if defined(_WIN32)
  #define ALIGN_OS ALIGN_OS_WIN
#else
  #define ALIGN_OS ALIGN_OS_MAC
#endif

//Detect compiler
#if defined(_MSC_VER)
  #if (_MSC_VER >= 1300)
    #define ALIGN_CC ALIGN_CC_MSVC7
  #else
    #define ALIGN_CC ALIGN_CC_MSVC
  #endif
#elif defined(__clang__) // make a guess that should work generically
  #define ALIGN_CC ALIGN_CC_CLANG
#else
  #define ALIGN_CC ALIGN_CC_GCC
#endif

//Detect processor
#if defined(_M_IX86) || defined(__INTEL__)
  #define ALIGN_PROC ALIGN_PROC_x86
#elif defined(__POWERPC__)
  #define ALIGN_PROC ALIGN_PROC_POWERPC
#elif defined(_M_X64) || (__LP64__)
  #define ALIGN_PROC ALIGN_PROC_x64
#endif

//Deduce endian
#define ALIGN_ENDIAN ALIGN_ENDIAN_LITTLE

// Detect size of a pointer in bits
// FIX ME: are these assumptions decent?
#if ((ALIGN_OS == ALIGN_OS_WIN) && (ALIGN_PROC == ALIGN_PROC_x86))
  #define ALIGN_POINTER_SIZE 32
#elif (ALIGN_PROC == ALIGN_PROC_x64)
  #define ALIGN_POINTER_SIZE 64
#else
  #error Can't deduce the size of a pointer
#endif

/*! \def CLIB_NS

  When including the C Runtime Library functions via the C++ headers, such as cmath and cassert
the functions are supposed to be placed in the std namespace.  Some compilers do not do this.  
Therefore CLIB_NS is designed to be used to prepend all access to the C runtime functions, and will
be appropriately defined by the SDK depending on compiler and platform.
*/
#ifndef CLIB_NS
#define CLIB_NS
#endif

// DEBUG_ONLY macro is reserved in MFC, but it introduces unnecessary brackets around f,
// so we have to use lower case for macro name here (it resembles macro 'assert' in that respect)
#ifndef NDEBUG
  #define debug_only(f) f
#else
  #define debug_only(f)
#endif

// VERIFY macro is reserved in MFC, this one is the same (for code that is compiled without MFC)
#ifndef VERIFY
  #ifndef NDEBUG
    #define VERIFY(f) assert(f)
  #else
    #define VERIFY(f) ((void)(f))
  #endif
#endif

// checks assert condition in Debug configurations, 
// and if the condition is not true does something in all configurations
#define assert_else(x) assert(x); if (!(x))

// define standard move constructor and move assignment for a class, provided it has swap() method
#if ALIGN_CC == ALIGN_CC_CLANG
#define DEFINE_MOVE(CLASS) 
#else
#define DEFINE_MOVE(CLASS) \
  CLASS(CLASS && i) { swap(i); } \
  CLASS & operator =(CLASS && i) { swap(i); return * this; }
#endif

// define default constructor as well
#define DEFINE_DEF_MOVE(CLASS) \
  CLASS() { } \
  DEFINE_MOVE(CLASS)

// some CLANG STL methods have nonstandard noexcept
#if ALIGN_CC == ALIGN_CC_CLANG
#define CLANG_NOEXCEPT noexcept
#else
#define CLANG_NOEXCEPT
#endif

// ignore unused variable warning
template <class T> inline void ignoreUnusedVariableWarning(T const&) {}
