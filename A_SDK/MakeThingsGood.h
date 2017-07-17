#pragma once

#include "Exception/Throw.h"

#ifdef SDK_EXPORTS
  #define COMMON_EXPORT_CLASS             _EXPORT_ATTR_
  #define COMMON_EXPORT_FUN               _EXPORT_ATTR_
#else 
  #define COMMON_EXPORT_CLASS             _IMPORT_ATTR_
  #define COMMON_EXPORT_FUN               _IMPORT_ATTR_
#endif

void COMMON_EXPORT_FUN hackToForceGenerationOfStaticLib();

namespace A_SDK
{
  // Follow to C_Client for the weird stuff.
  template <typename T>
  void makeThingsGood()
  {
    // plain 'throw' will lead to linker error as well
	std::throw_with_nested(ExceptionBase<std::runtime_error>("Cannot build T"));
  }
}
