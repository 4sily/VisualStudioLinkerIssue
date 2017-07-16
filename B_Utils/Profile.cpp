#include <Common/Common.h>
#include "Profile.h"

void B_Utils::hackToForceGenerationOfStaticLib() {}

B_Utils::Error::Error(std::string&& s) : ExceptionBaseClass(std::move(s)) { }
