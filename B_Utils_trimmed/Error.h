#include "ThrowChild.h"

#if defined(B_EXPORTS)
#define _B_UTILS_EXPORTS_CLASS      __declspec(dllexport)
#else
#define _B_UTILS_EXPORTS_CLASS      __declspec(dllimport)
#endif

struct
    _B_UTILS_EXPORTS_CLASS  // !!! Comment this line --> Build succeeds
    Error : public ExceptionBase<int>
{
    // definition is located in *.cpp file to enforce the generation of static library (B_Utils.lib)
    Error();

    // making Error() inline (and removing reference to B_Utils) causes an 'unresolved external' linker error.  (??)
};
