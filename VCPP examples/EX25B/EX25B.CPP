// ex25b.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ex25b.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx25bApp

BEGIN_MESSAGE_MAP(CEx25bApp, CWinApp)
    //{{AFX_MSG_MAP(CEx25bApp)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
    // Standard file based document commands
    ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
    ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx25bApp construction

CEx25bApp::CEx25bApp()
{
    // TODO: add construction code here,
    // Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CEx25bApp object

CEx25bApp NEAR theApp;


/////////////////////////////////////////////////////////////////////////////
// CEx25bApp initialization

BOOL CEx25bApp::InitInstance()
{
    TRACE("Entering CEx25bApp::InitInstance\n");
    if (!AfxOleInit()) {
      AfxMessageBox(IDP_OLE_INIT_FAILED);
      return FALSE;
    }
    if (RunEmbedded() || RunAutomated()) {
      COleTemplateServer::RegisterAll();
      return TRUE;
    }
    AfxMessageBox("EX25B cannot be run stand-alone\n");
    COleObjectFactory::UpdateRegistryAll();
    return FALSE;
}

int CEx25bApp::ExitInstance()
{
    TRACE("Entering CEx25bApp::ExitInstance\n");
    return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// CEx25bApp commands
