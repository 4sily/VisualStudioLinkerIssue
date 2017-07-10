#pragma once

#include "ExceptionBase.h"
#include "nested_exception.h"

#define MY_THROW(BaseException, message) \
  std::throw_with_nested(ExceptionBase<BaseException>(message))
