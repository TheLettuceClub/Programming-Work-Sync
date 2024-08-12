// mainfrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ex19c.h"

#include "poemdoc.h"
#include "stringvw.h"
#include "hexvw.h"
#include "mainfrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
    //{{AFX_MSG_MAP(CMainFrame)
    ON_WM_CREATE()
    ON_COMMAND(ID_WINDOW_NEW1, OnWindowNew1)
    ON_COMMAND(ID_WINDOW_NEW2, OnWindowNew2)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// arrays of IDs used to initialize control bars

// toolbar buttons - IDs are command buttons
static UINT BASED_CODE buttons[] =
{
    // same order as in the bitmap 'toolbar.bmp'
    ID_FILE_NEW,
    ID_FILE_OPEN,
    ID_FILE_SAVE,
        ID_SEPARATOR,
    ID_EDIT_CUT,
    ID_EDIT_COPY,
    ID_EDIT_PASTE,
        ID_SEPARATOR,
    ID_FILE_PRINT,
    ID_APP_ABOUT,
    ID_CONTEXT_HELP,
};

static UINT BASED_CODE indicators[] =
{
    ID_SEPARATOR,           // status line indicator
    ID_INDICATOR_CAPS,
    ID_INDICATOR_NUM,
    ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
    // TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    if (!m_wndToolBar.Create(this) ||
        !m_wndToolBar.LoadBitmap(IDR_MAINFRAME) ||
        !m_wndToolBar.SetButtons(buttons,
          sizeof(buttons)/sizeof(UINT)))
    {
        TRACE("Failed to create toolbar\n");
        return -1;      // fail to create
    }

    if (!m_wndStatusBar.Create(this) ||
        !m_wndStatusBar.SetIndicators(indicators,
          sizeof(indicators)/sizeof(UINT)))
    {
        TRACE("Failed to create status bar\n");
        return -1;      // fail to create
    }

    return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
void CMainFrame::OnWindowNew1() // ordinary text view
{
    CMDIChildWnd* pActiveChild = MDIGetActive();
    CDocument* pDocument;
    if (pActiveChild == NULL ||
       (pDocument = pActiveChild->GetActiveDocument()) == NULL)
    {
        TRACE0("Warning: No active document for WindowNew command\n");
        AfxMessageBox(AFX_IDP_COMMAND_FAILURE);
        return;     // command failed
    }

    // otherwise we have a new frame!
    CDocTemplate* pTemplate = ((CEx19cApp*) AfxGetApp())->m_pTemplate1;
    ASSERT_VALID(pTemplate);
    CFrameWnd* pFrame = pTemplate->CreateNewFrame(pDocument, pActiveChild);
    if (pFrame == NULL)
    {
        TRACE0("Warning: failed to create new frame\n");
        AfxMessageBox(AFX_IDP_COMMAND_FAILURE);
        return;     // command failed
    }

    pTemplate->InitialUpdateFrame(pFrame, pDocument);
}

void CMainFrame::OnWindowNew2() // hex dump view
{
    CMDIChildWnd* pActiveChild = MDIGetActive();
    CDocument* pDocument;
    if (pActiveChild == NULL ||
       (pDocument = pActiveChild->GetActiveDocument()) == NULL)
    {
        TRACE0("Warning: No active document for WindowNew command\n");
        AfxMessageBox(AFX_IDP_COMMAND_FAILURE);
        return;     // command failed
    }

    // otherwise we have a new frame!
    CDocTemplate* pTemplate = ((CEx19cApp*) AfxGetApp())->m_pTemplate2;
    ASSERT_VALID(pTemplate);
    CFrameWnd* pFrame = pTemplate->CreateNewFrame(pDocument, pActiveChild);
    if (pFrame == NULL)
    {
        TRACE0("Warning: failed to create new frame\n");
        AfxMessageBox(AFX_IDP_COMMAND_FAILURE);
        return;     // command failed
    }

    pTemplate->InitialUpdateFrame(pFrame, pDocument);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
    CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
    CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

