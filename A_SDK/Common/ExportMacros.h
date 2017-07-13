#pragma once

#define _EXPORT_ATTR_ __declspec(dllexport)
#define _IMPORT_ATTR_ __declspec(dllimport)

#define _EXPORT_CLASS_  _EXPORT_ATTR_
#define _IMPORT_CLASS_  _IMPORT_ATTR_
#define _EXPORT_FUN_    _EXPORT_ATTR_
#define _IMPORT_FUN_    _IMPORT_ATTR_

#ifdef SDK_EXPORTS
  #define COMMON_EXPORT             _EXPORT_CLASS_
  #define COMMON_EXPORT_CLASS       _EXPORT_CLASS_
  #define COMMON_EXPORT_FUNC        _EXPORT_FUNC_
  #define COMMON_EXPORT_FUN         _EXPORT_FUN_
#elif _MSC_VER >= 1600
  #define COMMON_EXPORT             
  #define COMMON_EXPORT_CLASS       
  #define COMMON_EXPORT_FUNC        _IMPORT_FUNC_
  #define COMMON_EXPORT_FUN         _IMPORT_FUN_
#else 
  #define COMMON_EXPORT             _IMPORT_CLASS_
  #define COMMON_EXPORT_CLASS       _IMPORT_CLASS_
  #define COMMON_EXPORT_FUNC        _IMPORT_FUNC_
  #define COMMON_EXPORT_FUN         _IMPORT_FUN_
#endif
