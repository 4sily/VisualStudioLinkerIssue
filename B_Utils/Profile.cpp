#include <Common/Common.h>
#include "Profile.h"

void B_Utils::hackToForceGenerationOfStaticLib() {}

Error::Error(std::string&& s) : ExceptionBaseClass(std::move(s)) { }
