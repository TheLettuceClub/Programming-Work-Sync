// ex25d.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ex25d.h"

#include "mainfrm.h"
#include "about.h"
#include "ex25ddoc.h"
#include "ex25dvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx25dApp

BEGIN_MESSAGE_MAP(CEx25dApp, CWinApp)
	//{{AFX_MSG_MAP(CEx25dApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx25dApp construction

CEx25dApp::CEx25dApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CEx25dApp object

CEx25dApp NEAR theApp;

// This identifier was generated to be statistically unique for your app.
// You may change it if you prefer to choose a specific identifier.
static const CLSID BASED_CODE clsid =
{ 0xba4d7e0, 0x2494, 0x101b, { 0xac, 0x24, 0x0, 0xaa, 0x0, 0x3e, 0x6f, 0x98 } };

/////////////////////////////////////////////////////////////////////////////
// CEx25dApp initialization

BOOL CEx25dApp::InitInstance()
{
	TRACE("Entering CEx25dApp::InitInstance\n");
	// Initialize OLE 2.0 libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.


	// Connect the COleTemplateServer to the document template.
	//  The COleTemplateServer creates new documents on behalf
	//  of requesting OLE containers by using information
	//  specified in the document template.

	// Parse the command line to see if launched as OLE server
	SetDialogBkColor();        // Set dialog background color to gray
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)
	
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.
	
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CEx25dDoc),
		RUNTIME_CLASS(CMainFrame),     // main SDI frame window
		RUNTIME_CLASS(CEx25dView));
	AddDocTemplate(pDocTemplate);
	m_server.ConnectTemplate(clsid, pDocTemplate, TRUE);
	if (RunEmbedded() || RunAutomated())
	{
		// Register all OLE server (factories) as running.  This enables the
		//  OLE 2.0 libraries to create objects from other applications.
		COleTemplateServer::RegisterAll();
		// Application was run with /Embedding or /Automation.  Don't show the
		//  main window in this case. (Do not call OnFileNew)
		return TRUE;
	}
	else {
		m_server.UpdateRegistry(OAT_DISPATCH_OBJECT);
		COleObjectFactory::UpdateRegistryAll();

        AfxMessageBox("EX25D must be run with OLE");

		// When a server application is launched stand-alone, it is a good idea
		//  to update the system registry in case it has been damaged.

		return FALSE;
	}
}

int CEx25dApp::ExitInstance()
{
	TRACE("Entering CEx25dApp::ExitInstance\n");
	return CWinApp::ExitInstance();
}

CAboutDlg::CAboutDlg(CWnd* pParent) : CDialog(CAboutDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CEx25dApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CEx25dApp commands
