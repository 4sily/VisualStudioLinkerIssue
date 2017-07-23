# Table of contents
<!-- TOC -->

- [Table of contents](#table-of-contents)
- [Visual Studio linker issue: when __declspec(dllimport) meets template class](#visual-studio-linker-issue-when-__declspecdllimport-meets-template-class)
- [Problem description](#problem-description)
- [Essence of the problem](#essence-of-the-problem)
- [Repository contents](#repository-contents)
- [Steps to reproduce](#steps-to-reproduce)
- [Workaround](#workaround)
- [Hypothesis](#hypothesis)
- [Discussion](#discussion)

<!-- /TOC -->
# Visual Studio linker issue: when __declspec(dllimport) meets template class
A toy sample that showcases an issue with Visual Studio linker which I'm failing to explain.

From first look this issue might seem relevant old bug in VS2010 (see [on StackOverflow](https://stackoverflow.com/questions/17987171/inherit-from-stdstring-without-npos-problems-in-dlls)).
But the error is different: no _"unresolved external symbol"_, but _"already defined"_ instead.

# Problem description

This problem has been discovered in a large Visual Studio solution (~200 projects) that belongs to a proprietary code base.

I've been developing a (yet another) small library for exception handling, and during its integration I've noticed that it's causing a strange linker error. Luckily, I've found a simple workaround (see below). But the question about the root cause remained. So the follow-up was:

1. I trimmed down the initial 'behemoth' solution into 3 projects, each with just several files. 
2. Then I managed to reproduced the same issue in a solution created from scratch. 
3. Then I've got the same result once I converted the solution and the projects to the latest Visual Studio.

The resulting repro-case is expressed by this repository.

# Essence of the problem

Assume we have 3 DLL's: **A_SDK**, **B_Utils** and **C_Client**.

(**UPDATE**: they don't have to be DLL's, what matters is using declspec(dllimport), [see](https://github.com/4sily/VisualStudioLinkerIssue/issues/4))

**UPDATE 2**: Actually, 2 DLL's is enough to expose the same problem in Debug x64. See `LinkerIssue_VS2017_trimmed.sln`. This new minimalistic solution contains of 2 projects, 5 source files. For details, check [this StackOverflow answer](https://stackoverflow.com/a/45245389/5722863).

These 3 projects form the following dependency graph:

* **B_Utils** --> **A_SDK**
* **C_Client** --> **B_Utils**, **A_SDK**

**A_SDK** defines a template class and a template or inline utility function that may throw an exception being the instantiation of that template

```
(ExceptionBase.h)
template<typename T>
class ExceptionBase;

----

(foo.h)
#include "ExceptionBase.h"
inline void foo()
{
    // Usage of throw_with_nested is important here
    std::throw_with_nested(ExceptionBase<std::runtime_error>("Problem"));
}

```

**B_Utils** defines its own error class

```
(Error.h)
#include "ExceptionBase.h"

// Standard way to export the class to the clients of DLL.
#if defined(B_EXPORTS)  // B_EXPORTS is defined only during compilation of B_Utils
#define _B_UTILS_EXPORTS_CLASS      __declspec(dllexport)
#else
#define _B_UTILS_EXPORTS_CLASS      __declspec(dllimport)
#endif

struct _B_UTILS_EXPORTS_CLASS Error : public ExceptionBase<std::runtime_error>
{ Error(std::string&& s); } // ctor definition is in *.cpp file
```

**C_Client** includes headers from both **A_SDK** and **B_Utils**, *exactly like in the sample below*.
And then the build fails.

```
(TranslationUnit_1.cpp)
#include "A_SDK/foo.h"
#include "B_Utils/Error.h"      // !!! Comment this line --> Build succeeds
void TranslationUnit_1() { 
  foo();                        // !!! Comment this line --> Build succeeds
}
---
(TranslationUnit_2.cpp)
#include "A_SDK/foo.h"
void TranslationUnit_2() {
  foo();                        // !!! Comment this line --> Build succeeds
}
```

Note the problem persists only as long as **all** of the conditions listed above are satisfied:

1) 3 projects A,B,C with dependencies like described above, B->A, C->B, C->A;
2) template class in project A, instantiated within the header in that project;
3) DLL-exported class in project B which inherits from the same intantiation of template class from A;
4) project C with TWO tranlation units, at least one of them includes both 2) and 3)

# Repository contents

Repository contains 2 solutions and 2 sets of projects, one for VS2013, and another for VS2017.
The names of the project files for VS2013 are: A_SDK.vcxproj, B_Utils.vcxproj, C_Client.vcxproj.
Those for VS2017 have postfix "_2017". *The contents of the .vcxproj files are identical*, apart from the target Visual Studio version.

Solutions were tested on:
* '2013' - Microsoft Visual Studio 2013 Professional Update 4.
* '2017' - Microsoft Visual Studio 2017 Community, version 15.2 (26430.12).

Each of the projects uses precompiled headers, defined in A_SDK/Common/Common.h

Project files are trimmed to the bare minimum, so only a single configuration (Release x64) is enabled.
Other configurations may be re-enabled if needed, they produce the same result.

Only necessary files are left in each project. For instance, C_Client contains only 2.
The names are self-describing.

Small technical detail: since my error handling library uses std::nested_exception, which is not implemented in VS2013, I use copy-pasted implementation from VS2017 <exception> header to make it compile by VS2013.

When exploring the repository, pay attention to comments like this one:
```
// !!! Comment this line --> Build succeeds
```

Result:
```
3>B_Utils.lib(B_Utils.dll) : error LNK2005: "public: __cdecl ExceptionBase<class std::runtime_error>::ExceptionBase<class std::runtime_error>(class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const &)" (??0?$ExceptionBase@Vruntime_error@std@@@@QEAA@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z) already defined in TranslationUnit_2.obj
3>B_Utils.lib(B_Utils.dll) : error LNK2005: "public: virtual __cdecl ExceptionBase<class std::runtime_error>::~ExceptionBase<class std::runtime_error>(void)" (??1?$ExceptionBase@Vruntime_error@std@@@@UEAA@XZ) already defined in TranslationUnit_2.obj
3>B_Utils.lib(B_Utils.dll) : error LNK2005: "public: __cdecl ExceptionBase<class std::runtime_error>::ExceptionBase<class std::runtime_error>(class ExceptionBase<class std::runtime_error> const &)" (??0?$ExceptionBase@Vruntime_error@std@@@@QEAA@AEBV0@@Z) already defined in TranslationUnit_2.obj
3>D:\tmp\SDK-590\x64\Release\C_Client.dll : fatal error LNK1169: one or more multiply defined symbols found
```

# Steps to reproduce

* Clone the repository or download it.
* Open the solution - either for Visual Studio 2013 or 2017.
* Build solution.

# Workaround

Once I changed
```
struct _B_UTILS_EXPORTS_CLASS Error : public ExceptionBase<std::runtime_error>
{ Error(std::string&& s); } 
```
to
```
struct Error : public ExceptionBase<std::runtime_error>
{ _B_UTILS_EXPORTS_FUN Error(std::string&& s); } // ctor definition is in *.cpp file
```
the build is fine, and I'm still able to use B_Utils::Error class in its clients.
This was sufficient for my needs.
However, if this class were more complex, I would have to mark each of its public methods with _B_UTILS_EXPORTS_CLASS, which doesn't really look like a proper solution.

# Hypothesis
 	
My working hypothesis is the following. When I export the whole type via 

```
struct _B_UTILS_EXPORTS_CLASS Error : public ExceptionBase<std::runtime_error>
```
the template instantiation ExceptionBase<std::runtime_error> gets exported too. 

In the latter case, when I only export ctor: 
```
_B_UTILS_EXPORTS_CLASS Error();
```
the template instantiation is not exported, hence the linker sees only one symbol in C_Client. What I don't understand: why isn't it able to merge the symbols in the former case? Just like it happens e.g. for static libraries.

# Discussion

Posted questions:
* [at StackOverflow](https://stackoverflow.com/questions/45133791/visual-studio-linker-error-when-template-class-meets-declspecimport);
  + Many thanks to [Ofek Shilon](https://stackoverflow.com/users/89706/ofek-shilon) who investigated this issue further and found an even smaller reprocase - check `LinkerIssue_VS2017_trimmed.sln`.
* [at MSDN forum](https://social.msdn.microsoft.com/Forums/en-US/31927e7c-bd97-4083-8686-c8b7d59064e7/linker-error-when-template-class-meets-declspecimport);
* [via Visual Studio "send feedback"](https://developercommunity.visualstudio.com/content/problem/80966/linker-error-when-template-class-meets-declspecimp.html)
  + Visual Studio support team triaged this issue, and as a result they filed a bug. Currently investigation is ongoing.