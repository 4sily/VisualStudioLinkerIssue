#pragma once

#include "Exception/Throw.h"

void COMMON_EXPORT_FUN hackToForceGenerationOfStaticLib();

namespace A_SDK
{
  template <class T> T& build()
  {
    static T t;
    return t;
  }

  // Build object of class T using build() and wrap it to the SmartPtr. Throw exception, if object cannot be created.
  template <class T>
  std::unique_ptr<T> buildSmartPtr()
  {
    const T& t = build<T>();
    if (reinterpret_cast<intptr_t>(&t) % 100 == 42) // whatever condition that cannot be optimized out at compile-time
      MY_THROW(std::runtime_error, "Cannot build T");
    return std::make_unique<T>(t);
  }
} // namespace Scene_NS
