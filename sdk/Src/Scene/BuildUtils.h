#pragma once

#include "Exception/Throw.h"

void COMMON_EXPORT_FUN hackToForceGenerationOfStaticLib();

namespace A_SDK
{
  // !!! Move function implementation to *.cpp (stop inlining it) --> Build succeeds
  //  ^
  // This is understandable. Follow to C_Client for the weird stuff.
  inline void playRussianRoulette()
  {
    static int number;

    // Whatever condition that cannot be optimized out at compile-time.
    if (reinterpret_cast<intptr_t>(&number) % 6 == 0)
      MY_THROW(std::runtime_error, "Cannot build T");
  }
}
