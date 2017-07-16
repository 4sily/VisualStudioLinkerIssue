#pragma once

#include <Exception/Throw.h>

#if defined(B_EXPORTS)
#define _B_UTILS_EXPORTS_CLASS      _EXPORT_ATTR_
#define _B_UTILS_EXPORTS_FUN        _EXPORT_ATTR_
#else
#define _B_UTILS_EXPORTS_CLASS      _IMPORT_ATTR_
#define _B_UTILS_EXPORTS_FUN        _IMPORT_ATTR_
#endif

#include <string>

namespace B_Utils
{
    void _B_UTILS_EXPORTS_FUN hackToForceGenerationOfStaticLib();

    struct
        _B_UTILS_EXPORTS_CLASS  // !!! Comment this line --> Build succeeds
        Error : public ExceptionBase<std::runtime_error>
    {
        // definition is located in *.cpp file to enforce the generation of static library (B_Utils.lib)
        Error(std::string&& s);
    };
}