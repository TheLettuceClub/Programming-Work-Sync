// ex25c.cpp : Contains EX25C.DLL implementation and initialization
//              code.
//
#include "stdafx.h"
#include "ex25cres.h"       // ex25c resources
#include "prompt.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CPromptDlg, CDialog)
    //{{AFX_MSG_MAP(CPromptDlg)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

CPromptDlg::CPromptDlg(CWnd* pParent)
    : CDialog(CPromptDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CPromptDlg)
    m_longData = 0;
    m_strTextData = "";
    //}}AFX_DATA_INIT
}

void CPromptDlg::DoDataExchange(CDataExchange* pDX)
{
    //{{AFX_DATA_MAP(CPromptDlg)
    DDX_Text(pDX, IDC_LONG_DATA, m_longData);
    DDX_Text(pDX, IDC_TEXT_DATA, m_strTextData);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// Public C interface


/////////////////////////////////////////////////////////////////////////////
// Library init

class CEx25cDLL : public CWinApp
{
public:
    virtual BOOL InitInstance(); // Initialization
    virtual int ExitInstance();  // Termination (WEP-like code)
};

BOOL CEx25cDLL::InitInstance()
{
    TRACE("EX25C.DLL CEx25cDLL::InitInstance\n");
    SetDialogBkColor();     // gray dialogs in the DLL as well
    // do not call AfxOleInit or ::OleInitialize
    // OLE is already initialized by the client app
    COleTemplateServer::RegisterAll();
    return TRUE;
}

int CEx25cDLL::ExitInstance()
{
    TRACE("EX25C.DLL CEx25cDLL::ExitInstance\n");
    // any DLL termination goes here (WEP-like code)
    return CWinApp::ExitInstance();
}

CEx25cDLL  NEAR Ex25cDLL;

/////////////////////////////////////////////////////////////////////////////
