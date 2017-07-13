# Visual Studio linker issue example
A toy sample that showcases an issue with Visual Studio linker which I'm failing to explain.

From first look this issue might seem relevant old bug in VS2010 (see [on StackOverflow](https://stackoverflow.com/questions/17987171/inherit-from-stdstring-without-npos-problems-in-dlls)).
But the error is different: no _"unresolved external symbol"_, but _"already defined"_ instead.

# About this repository

Each of projects are DLL's.
Each uses precompiled headers, defined in A_SDK/Common/Common.h

Dependencies:
* B_Utils --> A_SDK
* C_Client --> B_Utils, A_SDK

Project files are trimmed to the bare minimum, so only a single configuration (Release x64) is enabled.
Other configurations may be re-enabled if needed, they produce the same result.

Only necessary files are left in each project. For instance, C_Client contains only 2.
The names are self-describing.

Pay attention to comments like this one:
```
// !!! Comment this line --> Build succeeds
```

# Details

See my question at StackOverflow - link to be added.

# Steps to reproduce

* Clone the repository or download it.
* Open the solution - either for Visual Studio 2013 or 2017 (to be added).
* Build solution.

Result:
```
3>B_Utils.lib(B_Utils.dll) : error LNK2005: "public: __cdecl ExceptionBase<class std::runtime_error>::ExceptionBase<class std::runtime_error>(class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const &)" (??0?$ExceptionBase@Vruntime_error@std@@@@QEAA@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z) already defined in TranslationUnit_2.obj
3>B_Utils.lib(B_Utils.dll) : error LNK2005: "public: virtual __cdecl ExceptionBase<class std::runtime_error>::~ExceptionBase<class std::runtime_error>(void)" (??1?$ExceptionBase@Vruntime_error@std@@@@UEAA@XZ) already defined in TranslationUnit_2.obj
3>B_Utils.lib(B_Utils.dll) : error LNK2005: "public: __cdecl ExceptionBase<class std::runtime_error>::ExceptionBase<class std::runtime_error>(class ExceptionBase<class std::runtime_error> const &)" (??0?$ExceptionBase@Vruntime_error@std@@@@QEAA@AEBV0@@Z) already defined in TranslationUnit_2.obj
3>D:\tmp\SDK-590\x64\Release\C_Client.dll : fatal error LNK1169: one or more multiply defined symbols found
```