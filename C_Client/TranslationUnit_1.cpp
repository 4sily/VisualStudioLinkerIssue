#include <Common/Common.h>

#include <A_SDK/Roulette.h>
#include <B_Utils/Profile.h>        // !!! Comment this line --> Build succeeds

void TranslationUnit_1()
{
  A_SDK::playRussianRoulette();     // !!! Comment this line --> Build succeeds
}
