#pragma once

template<
  typename BaseStdException
>
class ExceptionBase :
  public BaseStdException
{
public:
  static_assert(std::is_base_of<std::exception, BaseStdException>::value,
                "BaseException must inherit from std::exception");

  using ExceptionBaseClass = ExceptionBase;

  ExceptionBase(const std::string& i_message) :
    BaseStdException(i_message.c_str())
  {}
};
