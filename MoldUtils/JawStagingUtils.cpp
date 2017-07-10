#include <Common/Common.h>

// THIS
#include <FileTools/Profile.h>

struct Thing3D
{
  void deleteThis() {}
};

void setInitialJawOpeningToParamObject(int lowerJaw, float i_opening)
{
  Thing3D* param = nullptr;

  if (!param)
  {
    auto paramObj = Scene_NS::buildSmartPtr<Thing3D>();
    param = paramObj.release();
  }
}
