#pragma once

#define VC_EXTRALEAN        // Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN
#define WINVER 0x0601       // Windows 7
#define _WIN32_IE 0x0600    // Target IE 6

#pragma warning(push)
#if (defined _AFXDLL)
  #pragma warning(push) // save warning state because MFC headers corrupts it
  // We declare it further
  #ifdef VERIFY
    #undef VERIFY
  #endif

  #include <afxwin.h>         // MFC core and standard components
  #include <afxext.h>         // MFC extensions

  #ifndef _AFX_NO_AFXCMN_SUPPORT
    #include <afxcmn.h>       // MFC support for Windows Common Controls
  #endif // _AFX_NO_AFXCMN_SUPPORT

  #include <afxole.h>
  #include <afxdisp.h>
  #pragma warning(pop)        // restore warning state
  #if (_MSC_VER < 1800)
    #pragma warning(pop)      // pop twice because afxwin.h has a mismatched push
  #endif
#else
  #include <windows.h>
  #include <crtdbg.h>
  #define  TRACE(x)  dprintf(x)
  #define  ASSERT(x) _ASSERT(x)
  #include <ole2.h>
#endif
