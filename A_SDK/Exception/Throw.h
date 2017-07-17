#pragma once

#if defined(_MSC_VER) && _MSC_VER < 1900
#include "nested_exception.h" // Functionality not implemented by VS2013; remove this in VS2017.
#endif

template<typename BaseStdException>
class ExceptionBase : public BaseStdException
{
public:
  static_assert(std::is_base_of<std::exception, BaseStdException>::value,
                "BaseException must inherit from std::exception");

  using ExceptionBaseClass = ExceptionBase;

  ExceptionBase(const std::string& i_message) : BaseStdException(i_message.c_str()) {}
};
