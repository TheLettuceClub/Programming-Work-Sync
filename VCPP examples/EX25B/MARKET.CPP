// market.cpp : implementation file
//

#include "stdafx.h"
#include "ex25b.h"
#include "market.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMarket

IMPLEMENT_DYNCREATE(CMarket, CCmdTarget)

CMarket::CMarket()
{
    TRACE("Entering CMarket constructor -- %p\n", this);
    EnableAutomation();
    
    // To keep the application running as long as an OLE Automation 
    //  object is active, the constructor calls AfxOleLockApp.
    
    AfxOleLockApp();
}

CMarket::~CMarket()
{
    TRACE("Entering CMarket destructor -- %p\n", this);
    // To terminate the application when all objects are created
    //  with OLE Automation, the destructor calls AfxOleUnlockApp.
    
    AfxOleUnlockApp();
}

void CMarket::OnFinalRelease()
{
    // When the last reference for an automation object is released,
    //  OnFinalRelease is called.  This implementation deletes the 
    //  object.  Add additional cleanup required for your object before
    //  deleting it from memory.

    delete this;
}

BEGIN_MESSAGE_MAP(CMarket, CCmdTarget)
    //{{AFX_MSG_MAP(CMarket)
        // NOTE - the ClassWizard will add and remove mapping macros here.
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMarket, CCmdTarget)
    //{{AFX_DISPATCH_MAP(CMarket)
    DISP_FUNCTION(CMarket, "GetIndustrialsAverage", GetIndustrialsAverage, VT_I2, VTS_VARIANT)
    //}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

IMPLEMENT_OLECREATE(CMarket, "EX25B.MARKET", 0xaa41dd80, 0x419a,
                    0x101b, 0xac, 0x24, 0x0, 0xaa, 0x0, 0x3e,
                    0x6f, 0x98)

/////////////////////////////////////////////////////////////////////////////
// CMarket message handlers


short CMarket::GetIndustrialsAverage(const VARIANT FAR& Date)
{
    TRACE("CMarket::GetIndustrialsAverage - %p, Date = %f\n",
           this, Date.dblVal);
    long lRand = rand();
    return (short) (Date.dblVal - 30600.0) +
           (short) (lRand * 40 / RAND_MAX) - 20;
}
