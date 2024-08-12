#include "stdafx.h"
#include "ex22a.h"

CEx22aApp NEAR theApp; // the one and only CEx22aApp object

BOOL CEx22aApp::InitInstance()
{
    m_pMainWnd = new CMainFrame();
    ASSERT(m_pMainWnd != NULL); // error checking only
    m_pMainWnd->ShowWindow(m_nCmdShow);
    m_pMainWnd->UpdateWindow();
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
    //{{AFX_MSG_MAP(CMainFrame)
    ON_WM_PAINT()
    ON_WM_CLOSE()
    ON_WM_QUERYENDSESSION()
    ON_COMMAND(ID_FILE, OnFile)
    ON_COMMAND(ID_HLP, OnHlp)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////
CMainFrame::CMainFrame()
{
    Create(NULL, "EX22A Application",
           WS_OVERLAPPEDWINDOW, rectDefault, NULL,
           MAKEINTRESOURCE(IDR_MAINFRAME));
}

/////////////////////////////////////////////////////////////////////////
void CMainFrame::OnPaint()
{
    CPaintDC dc(this);
    dc.TextOut(0, 0, "Hello, world!");
}

/////////////////////////////////////////////////////////////////////////
void CMainFrame::OnClose()
{
    if (AfxMessageBox("OK to close window?", MB_YESNO) == IDYES) { 
        CFrameWnd::OnClose();
    }
}

/////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::OnQueryEndSession()
{
    // received when user quits Windows
    SendMessage(WM_CLOSE);
    return TRUE;
}

// menu command handlers
/////////////////////////////////////////////////////////////////////////
void CMainFrame::OnFile()
{
    TRACE("Entering CMainFrame::OnFile\n");
}

/////////////////////////////////////////////////////////////////////////
void CMainFrame::OnHlp()
{
    TRACE("Entering CMainFrame::OnHlp\n");
}
