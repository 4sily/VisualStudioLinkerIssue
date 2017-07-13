#pragma once

#if defined(__clang__)
  #define _EXPORT_CLASS_
  #define _IMPORT_CLASS_

  #define _EXPORT_FUNC_(...) __VA_ARGS__
  #define _IMPORT_FUNC_(...) __VA_ARGS__
#elif defined(_MSC_VER)
  #define _EXPORT_ATTR_ __declspec(dllexport)
  #define _IMPORT_ATTR_ __declspec(dllimport)

  #define _EXPORT_CLASS_  _EXPORT_ATTR_
  #define _IMPORT_CLASS_  _IMPORT_ATTR_
  #define _EXPORT_FUN_    _EXPORT_ATTR_
  #define _IMPORT_FUN_    _IMPORT_ATTR_

  // why?
  #define _EXPORT_FUNC_(...) _EXPORT_ATTR_ __VA_ARGS__
  #define _IMPORT_FUNC_(...) _IMPORT_ATTR_ __VA_ARGS__
#endif

#ifdef SDK_EXPORTS
  #define COMMON_EXPORT             _EXPORT_CLASS_
  #define COMMON_EXPORT_CLASS       _EXPORT_CLASS_
  #define COMMON_EXPORT_FUNC        _EXPORT_FUNC_
  #define COMMON_EXPORT_FUN         _EXPORT_FUN_
  #define COMMON_EXPORT_CLASS1      _EXPORT_CLASS_
// sometimes in Visual Studio 2010 __declspec(dllimport) specifier
// causes linker errors:
// https://connect.microsoft.com/VisualStudio/feedback/details/562448/std-string-npos-lnk2001-when-inheriting-a-dll-class-from-std-string#details
// As a workaround, we are trying not to use __declspec(dllimport) for importing SDK classes
#elif _MSC_VER >= 1600
  #define COMMON_EXPORT             
  #define COMMON_EXPORT_CLASS       
  #define COMMON_EXPORT_FUNC        _IMPORT_FUNC_
  #define COMMON_EXPORT_FUN         _IMPORT_FUN_
// using COMMON_EXPORT_CLASS1 when we really need __declspec(dllimport)
  #define COMMON_EXPORT_CLASS1      _IMPORT_CLASS_
#else 
  #define COMMON_EXPORT             _IMPORT_CLASS_
  #define COMMON_EXPORT_CLASS       _IMPORT_CLASS_
  #define COMMON_EXPORT_FUNC        _IMPORT_FUNC_
  #define COMMON_EXPORT_FUN         _IMPORT_FUN_
  #define COMMON_EXPORT_CLASS1      _IMPORT_CLASS_
#endif
