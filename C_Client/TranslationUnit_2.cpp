#include <Common/Common.h>

#include <A_SDK/MakeThingsGood.h>

void TranslationUnit_2()
{
  A_SDK::makeThingsGood<double>();     // !!! Comment this line --> Build succeeds
}
