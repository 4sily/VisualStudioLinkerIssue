#include "Common/Common.h"

namespace Common_NS 
{ 
  using ResID = HINSTANCE;
  Common_NS::ResID s_localID = (HINSTANCE)0xFFFFFFFF; 
  Common_NS::ResID s_SDK_ID = (HINSTANCE)0xFFFFFFFF;
}

#if (ALIGN_OS == ALIGN_OS_WIN)

  HINSTANCE hInstance = 0;

  static AFX_EXTENSION_MODULE s_AlignSDKDLL = {NULL, NULL};

  BOOL WINAPI DllMain(HINSTANCE hinstDLL,ULONG fdwReason,LPVOID lpvReserved)
  {
    if( fdwReason == DLL_PROCESS_ATTACH )
    {
      hInstance = hinstDLL;

      if (!AfxInitExtensionModule(s_AlignSDKDLL, hinstDLL))
        return FALSE;

      new CDynLinkLibrary(hinstDLL, hinstDLL);
    }
    return TRUE;
  }

#endif

