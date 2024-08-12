// alarmc.h

#include "cvariant.h"

class CAlarmControl : public COleDispatchDriver
{
// Attributes
public:
    // These need to be in the same sequence as the server's
    //  dispatch map. If the server changes, update these.
    enum { DID_ZERO, DID_TIME };
    CVariant GetTime();
    void SetTime(const VARIANT&);
};

