#pragma once

#include <Exception/ExceptionBase.h>
#include <Common/ExportMacros.h>

#if   defined(FILETOOLS_EXPORTS)
#define _B_UTILS_EXPORTS_CLASS      _EXPORT_CLASS_
#define _B_UTILS_EXPORTS_FUNC(type) _EXPORT_FUNC_(type)
#else
#define _B_UTILS_EXPORTS_CLASS      _IMPORT_CLASS_
#define _B_UTILS_EXPORTS_FUNC(type) _IMPORT_FUNC_(type)
#endif

#include <string>

struct _B_UTILS_EXPORTS_CLASS Error
  : public ExceptionBase<std::runtime_error>
{
  // definition is located in *.cpp file to enforce the generation of static library (B_Utils.lib)
  Error(std::string&& s);
};
