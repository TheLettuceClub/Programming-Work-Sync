// ex20b.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ex20b.h"

#include "mainfrm.h"
#include "poemdoc.h"
#include "stringvw.h"
#include "hexvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx20bApp

BEGIN_MESSAGE_MAP(CEx20bApp, CWinApp)
	//{{AFX_MSG_MAP(CEx20bApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
	// Global help commands
	ON_COMMAND(ID_HELP_INDEX, CWinApp::OnHelpIndex)
	ON_COMMAND(ID_HELP_USING, CWinApp::OnHelpUsing)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CWinApp::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CWinApp::OnHelpIndex)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx20bApp construction

CEx20bApp::CEx20bApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CEx20bApp object

CEx20bApp NEAR theApp;

/////////////////////////////////////////////////////////////////////////////
// CEx20bApp initialization

BOOL CEx20bApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	SetDialogBkColor();        // set dialog background color to gray
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	AddDocTemplate(new CMultiDocTemplate(IDR_POEMTYPE,
			RUNTIME_CLASS(CPoemDoc),
			RUNTIME_CLASS(CMDIHelpWnd),        // standard MDI child frame
			RUNTIME_CLASS(CStringView)));

	m_pTemplate1 = new CMultiDocTemplate(IDR_POEMTYPE,
			RUNTIME_CLASS(CPoemDoc),
			RUNTIME_CLASS(CMDIHelpWnd),	
			RUNTIME_CLASS(CStringView));

	m_pTemplate2 = new CMultiDocTemplate(IDR_POEMTYPE,
			RUNTIME_CLASS(CPoemDoc),
			RUNTIME_CLASS(CMDIHelpWnd),	
			RUNTIME_CLASS(CHexView));
	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();
	m_pMainWnd = pMainFrame;

	// create a new (empty) document
	OnFileNew();

	if (m_lpCmdLine[0] != '\0')
	{
		// TODO: add command line processing here
	}

	return TRUE;
}

int CEx20bApp::ExitInstance()
{
	delete m_pTemplate1;
	delete m_pTemplate2;
	return CWinApp::ExitInstance(); // saves profile settings
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
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
void CEx20bApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CEx20bApp commands
