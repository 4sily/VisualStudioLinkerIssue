#include "Common/Common.h"

HINSTANCE hInstance = 0;

BOOL WINAPI DllMain(HINSTANCE hinstDLL, ULONG fdwReason, LPVOID lpvReserved)
{
  if (fdwReason == DLL_PROCESS_ATTACH)
  {
    hInstance = hinstDLL;
  }
  return TRUE;
}
