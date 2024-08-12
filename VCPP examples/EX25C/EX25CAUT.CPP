// ex25caut.cpp : implementation file
//

#include "stdafx.h"
#include "ex25cres.h"       // ex25c resources
#include "ex25caut.h"
#include "prompt.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////
// CEx25cAuto

IMPLEMENT_DYNCREATE(CEx25cAuto, CCmdTarget)

BEGIN_MESSAGE_MAP(CEx25cAuto, CCmdTarget)
    //{{AFX_MSG_MAP(CEx25cAuto)
        // NOTE - the ClassWizard will add and remove mapping
        //  macros here.
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CEx25cAuto, CCmdTarget)
    //{{AFX_DISPATCH_MAP(CEx25cAuto)
    DISP_PROPERTY(CEx25cAuto, "LongData", m_longData, VT_I4)
    DISP_PROPERTY(CEx25cAuto, "TextData", m_textData,
                  VT_VARIANT)
    DISP_FUNCTION(CEx25cAuto, "DisplayDialog", DisplayDialog,
                  VT_BOOL, VTS_NONE)
    //}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

IMPLEMENT_OLECREATE(CEx25cAuto, "Ex25c.auto", 0x97ef7fe1,
                    0x26d6, 0x101b, 0xac, 0x24, 0x0, 0xaa,
                    0x0, 0x3e, 0x6f, 0x98)

CEx25cAuto::CEx25cAuto() : m_textData("default")
{
    TRACE("Entering CEx25cAuto ctor %p\n", this);
    m_longData = 0L;
    EnableAutomation();
    
    // To keep the application running as long as an OLE
    //  Automation object is active, the constructor calls
    //  AfxOleLockApp.
    AfxOleLockApp();
}

CEx25cAuto::~CEx25cAuto()
{
    // To terminate the application when all objects
    //   are created with OLE Automation, the destructor
    //   calls AfxOleUnlockApp.
    
    TRACE("Entering CEx25cAuto dtor %p\n", this);
    AfxOleUnlockApp();
}

void CEx25cAuto::OnFinalRelease()
{
    // When the last reference for an automation object is
    //  released, OnFinalRelease is called. This implementation
    //  deletes the object. Add additional cleanup required for
    //  your object before deleting it from memory.

    TRACE("Entering CEx25cAuto::OnFinalRelease %p\n", this);
    delete this;
}

///////////////////////////////////////////////////////////////
// CEx25cAuto message handlers

BOOL CEx25cAuto::DisplayDialog()
{
    TRACE("Entering CEx25cAuto::DisplayDialog %p\n", this);
    BOOL bRet = TRUE;
    AfxLockTempMaps();  // see MFC Tech Note #3
    TRY {
      CPromptDlg dlg(CWnd::GetActiveWindow());
      ASSERT(m_textData.vt = VT_BSTR);
      dlg.m_strTextData = m_textData.bstrVal;
      dlg.m_longData = m_longData;
      if (dlg.DoModal() == IDOK) {
        m_textData = CVariant(dlg.m_strTextData);
        m_longData = dlg.m_longData;
        bRet = TRUE;
      }
      else {
        bRet =  FALSE;
      }
    }
    CATCH_ALL(e) {
      TRACE("Exception: failure to display dialog\n");
      bRet =  FALSE;
    }
    END_CATCH_ALL
    AfxUnlockTempMaps();
    return bRet;
}
