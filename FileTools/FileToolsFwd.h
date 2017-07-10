#pragma once

#include <Common/ExportMacros.h>

#if   defined(FILETOOLS_EXPORTS)
#define _FILETOOLS_EXPORTS_CLASS      _EXPORT_CLASS_
#define _FILETOOLS_EXPORTS_FUNC(type) _EXPORT_FUNC_(type)
#else
#define _FILETOOLS_EXPORTS_CLASS      _IMPORT_CLASS_
#define _FILETOOLS_EXPORTS_FUNC(type) _IMPORT_FUNC_(type)
#endif

#include <string>

namespace FileTools_NS
{
  enum TreatmentStage;
}

class _FILETOOLS_EXPORTS_CLASS Profile;

namespace CSV
{
  _FILETOOLS_EXPORTS_FUNC(std::string) field( const char* i_value );
  _FILETOOLS_EXPORTS_FUNC(char) sep();

}
