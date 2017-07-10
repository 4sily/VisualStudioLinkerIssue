#include <Common/Common.h>

void TranslationUnit_2(int lowerJaw, float i_opening)
{
  struct S {};
  A_SDK::build<S>();                // !!! Comment this line --> Build succeeds
}
