#include <Common/Common.h>

#include <A_SDK/MakeThingsGood.h>
#include <B_Utils/Error.h>        // !!! Comment this line --> Build succeeds

void TranslationUnit_1()
{
  A_SDK::makeThingsGood<int>();     // !!! Comment this line --> Build succeeds
}
