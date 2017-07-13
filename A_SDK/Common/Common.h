#pragma once

#include "Common/ExportMacros.h"

#define WINVER 0x0601       // Windows 7

#if (defined _AFXDLL)
#include <afxwin.h>
#include <afxole.h>
#include <afxdisp.h>
#else
#include <windows.h>
#endif

#include <cctype>
#include <stdexcept>
