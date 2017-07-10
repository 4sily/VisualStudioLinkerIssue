#pragma once

#include "Common/ExportMacros.h"
#include "Common/PlatformMacros.h"

// Remove deprecated stuff
#define _HAS_OLD_IOSTREAMS_MEMBERS 0
#define _HAS_FUNCTION_ASSIGN 0
#define _HAS_AUTO_PTR_ETC 0

#if _MSC_VER > 1200
# define ALIGN_STDEXT stdext
# ifndef _DEBUG
#  undef _SECURE_SCL
#  define _SECURE_SCL 0 // disable secure iterators to improve performance
# endif // _DEBUG
#else // _MSC_VER
# define ALIGN_STDEXT std
#endif // _MSC_VER

// New types
class COMMON_EXPORT_CLASS ClassID;
class COMMON_EXPORT_CLASS Param;
class COMMON_EXPORT_CLASS ParamContainer;
class COMMON_EXPORT_CLASS MapParamContainer;

// disable lexical_cast conversion
// for CString
#include "Common/LexicalCastWorkaround.h"

// Custom string classes
class COMMON_EXPORT_CLASS ZString;
class COMMON_EXPORT_CLASS Utf8WString;

// I18N support
namespace Common_NS
{
  class COMMON_EXPORT_CLASS LanguageManager;
  class COMMON_EXPORT_CLASS Localizer;
  class COMMON_EXPORT_CLASS LocString;
}
class COMMON_EXPORT_CLASS UIString;

// CRC support
//! \todo move to Util
class COMMON_EXPORT_CLASS CRC32;

//**************************************
// Turn off useless PC warnings
#ifdef _MSC_VER
  #pragma warning ( disable : 4273 )    // Warning: 'Func' : inconsistent dll linkage.  dllexport assumed.
  #pragma warning ( disable : 4275 )    // Warning: non dll-interface class 'Foo' used as base for dll-interface class 'Bar'
  #pragma warning ( disable : 4251 )    // Warning: 'Foo instance, member of Bar' : class 'Foo' needs to have dll-interface to be used by clients of class 'Bar'
  #pragma warning ( disable : 4800 ) // forcing value to bool 'true' or 'false' (performance warning)
  #pragma warning ( disable : 4018 ) // put signed/unsigned comparison mismatch warning at level 4 --Sam
  #pragma warning ( disable : 4244 ) // put conversion from 'float' to 'double' data loss warning at level 4 --Sam
  #pragma warning ( disable : 4100 ) // Warning: unreferenced formal parameter (level 4->disabled)
#if (_MSC_VER >= 1400)
  #pragma warning ( disable : 4996 ) // Warning: deprecated functions
#endif

//**************************************
// #define DEBUG to something useful
#ifdef _DEBUG
  #define DEBUG
#else
  #undef DEBUG
#endif

#endif  
