#include "FileToolsFwd.h"

#include <Exception/ExceptionBase.h>

struct _FILETOOLS_EXPORTS_CLASS Error
  : public ExceptionBase<std::runtime_error>
{
  Error(std::string&& s) : ExceptionBase<std::runtime_error>(std::move(s)) { }
};
