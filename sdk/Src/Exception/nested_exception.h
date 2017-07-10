#pragma once

#include <exception>

/// \file
/// This file contains an implementation of class std::nested_exception and several functions related to that.
/// This implementation is copied from VS2017's <exception> header and adapted to VS2013 compiler.
/// Actually, it is a hack to work around the lack of support for std::nested_exception in VS2013.
/// TODO: remove it after the transition to the modern toolchain that supports this C++11 feature.
namespace std
{
  // A placeholder implementation for std::nested_exception missing in VS2013
  // taken from VS2017's <exception> header

  // CLASS nested_exception
  class nested_exception
  { // wrap an exception_ptr
  public:
    nested_exception() _NOEXCEPT
      : _Exc(_XSTD current_exception())
    { // default construct
    }

    nested_exception(const nested_exception&) /*noexcept*/ = default;
    nested_exception& operator=(const nested_exception&) /*noexcept*/ = default;
    virtual ~nested_exception() = default;

    void rethrow_nested() const
    {	// throw wrapped exception_ptr
      if (_Exc)
        _XSTD rethrow_exception(_Exc);
      else
        _XSTD terminate();
    }

    _XSTD exception_ptr nested_ptr() const _NOEXCEPT
    {	// return wrapped exception_ptr
      return (_Exc);
    }

  private:
    _XSTD exception_ptr _Exc;
  };

  // TEMPLATE FUNCTION throw_with_nested
  template<class _Ty,
  class _Uty>
  struct _With_nested
    : _Uty, nested_exception
  {	// glue user exception to nested_exception
    explicit _With_nested(_Ty&& _Arg)
      : _Uty(_STD forward<_Ty>(_Arg)), nested_exception()
    {	// store user exception and current_exception()
    }
  };

  template<class _Ty>
  inline void _Throw_with_nested(_Ty&& _Arg, true_type)
  {	// throw user exception glued to nested_exception
    typedef typename remove_reference<_Ty>::type _Uty;
    typedef _With_nested<_Ty, _Uty> _Glued;

    _THROW_NCEE(_Glued, _STD forward<_Ty>(_Arg));
  }

  template<class _Ty>
  inline void _Throw_with_nested(_Ty&& _Arg, false_type)
  {	// throw user exception by itself
    typedef typename decay<_Ty>::type _Decayed;

    _THROW_NCEE(_Decayed, _STD forward<_Ty>(_Arg));
  }

  template<class _Ty>
  inline void throw_with_nested(_Ty&& _Arg)
  {	// throw user exception, glued to nested_exception if possible
    typedef typename remove_reference<_Ty>::type _Uty;

    integral_constant < bool,
      is_class<_Uty>::value
      && !is_base_of<nested_exception, _Uty>::value
      /*&& !is_final<_Uty>::value*/ > _Tag;

    _Throw_with_nested(_STD forward<_Ty>(_Arg), _Tag);
  }

  // TEMPLATE FUNCTION rethrow_if_nested
  template<class _Ty> inline
    void _Rethrow_if_nested(const _Ty *_Ptr, true_type)
  {	// use dynamic_cast
    const auto _Nested = dynamic_cast<const nested_exception *>(_Ptr);

    if (_Nested)
      _Nested->rethrow_nested();
  }

  template<class _Ty> inline
    void _Rethrow_if_nested(const _Ty *, false_type)
  {	// can't use dynamic_cast
  }

  template<class _Ty> inline
    void rethrow_if_nested(const _Ty& _Arg)
  {	// detect nested_exception inheritance
    integral_constant < bool,
      is_polymorphic<_Ty>::value
      && (!is_base_of<nested_exception, _Ty>::value
      || is_convertible<_Ty *, nested_exception *>::value) > _Tag;

    _Rethrow_if_nested(_STD addressof(_Arg), _Tag);
  }
}
