#include <Common/Common.h>
#include "Profile.h"

Error::Error(std::string&& s) : ExceptionBaseClass(std::move(s)) { }
