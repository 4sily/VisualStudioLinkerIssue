#pragma once

#include "Exception/AlignException.h"

namespace COM_NS
{
  struct ComObjectDelete
  {
    template<class T>
    void operator()(T* ptr) const
    {
      if (ptr)
        ptr->deleteThis();
    }
  };

  template<class T> using SmartPtr = std::unique_ptr < T, ComObjectDelete > ;
}

namespace Scene_NS 
{
  void COMMON_EXPORT_FUN justToMakeSureThatStaticLibGetsGenerated();

  template <class T> T *build()
  {
    static T t;
    return &t;
  }

  // Build object of class T using build() and wrap it to the SmartPtr. Throw exception, if object cannot be created.
  template <class T>
  COM_NS::SmartPtr<T> buildSmartPtr()
  {
    T* t = build<T>();
    if (!t)
      ALIGN_THROW_DECORATED(std::runtime_error, "Cannot build T");
    return COM_NS::SmartPtr<T>(t);
  }
} // namespace Scene_NS
