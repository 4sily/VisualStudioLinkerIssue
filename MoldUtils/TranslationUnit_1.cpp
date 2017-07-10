#include <Common/Common.h>

#include <FileTools/Profile.h>      // !!! Comment this line --> Build succeeds

void TranslationUnit_1(int i_jp)
{
  struct S {};
  A_SDK::build<S>();                // !!! Comment this line --> Build succeeds
}
