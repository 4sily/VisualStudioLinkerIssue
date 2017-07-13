#pragma once

#include "Common/CommonFwd.h"
#include "Common/PlatformMacros.h"

#if ALIGN_OS == ALIGN_OS_WIN
  #include "Common/WinCommon.h"
#elif ALIGN_OS == ALIGN_OS_MAC
  #include "Common/MacCommon.h"
#endif

//**************************************
// Make dead certain that max and min are not macros
#ifdef max
  #undef max
#endif

#ifdef min
  #undef min
#endif
