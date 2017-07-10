#include <Common/Common.h>

class AttachmentJournal
{
public:
  void deleteThis() {}
};

void getOrCreate(int i_jp)
{
  Scene_NS::buildSmartPtr<AttachmentJournal>();
}
