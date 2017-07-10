#include <Common/Common.h>
#include "Profile.h"

HINSTANCE hInstance = NULL;

BOOL WINAPI DllMain(HINSTANCE hinstDLL,ULONG fdwReason,LPVOID lpvReserved)
{
  if( fdwReason == DLL_PROCESS_ATTACH )
  {
    hInstance = hinstDLL;
  }
  return TRUE;
}
