// clockc.h

/////////////////////////////////////////////////////////////////////////////
// CClockControl wrapper class
#include "cvariant.h"

class CClockControl : public COleDispatchDriver
{
// Attributes
public:
    // These need to be in the same sequence as the server's
    //  dispatch map. If the server changes, update these.
    enum { DID_ZERO, DID_TIME, DID_REFRESH,
           DID_SHOW, DID_CREATEALARM, DID_FIGURE };
    CVariant GetFigure(short i);
    void SetFigure(short i, const VARIANT&);
    CVariant GetTime();
    void SetTime(const VARIANT&);

// Operations
public:
    void ShowWin();
    void RefreshWin();
    LPDISPATCH CreateAlarm(const VARIANT& time);
};

