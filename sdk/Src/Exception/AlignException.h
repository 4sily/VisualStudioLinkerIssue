#pragma once

#include "ExceptionBase.h"
#include "nested_exception.h"

#define ALIGN_MAKE_EXCEPTION_DECORATED(BaseStdException, message) \
  ExceptionBase<BaseStdException>(message)

#define ALIGN_THROW_DECORATED(BaseException, message) \
  std::throw_with_nested(ALIGN_MAKE_EXCEPTION_DECORATED(BaseException, message))
