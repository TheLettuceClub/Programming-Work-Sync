#include "stdafx.h"
#include "ex22c.h"

CEx22cApp NEAR theApp; // the one and only CEx22cApp object

BOOL CEx22cApp::InitInstance()
{
    m_pMainWnd = new CMainFrame();
    m_pMainWnd->ShowWindow(m_nCmdShow);
    m_pMainWnd->UpdateWindow();
    new CChildFrame();
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
    //{{AFX_MSG_MAP(CMainFrame)
    ON_WM_CLOSE()
    ON_WM_QUERYENDSESSION()
    ON_COMMAND(ID_FILE_NEW, OnFileNew)
    ON_COMMAND(ID_WINDOW_CLOSE_ALL, OnWindowCloseAll)
    ON_UPDATE_COMMAND_UI(ID_WINDOW_CLOSE_ALL, OnUpdateWindowCloseAll)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////
CMainFrame::CMainFrame()
{
    Create(NULL, "EX22C Application",
           WS_OVERLAPPEDWINDOW,
           rectDefault, NULL,
           MAKEINTRESOURCE(IDR_MAINFRAME));
}

/////////////////////////////////////////////////////////////////////////
void CMainFrame::OnClose()
{
    if (CloseAllChildWindows()) {
        CMDIFrameWnd::OnClose();
    }
}

/////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::OnQueryEndSession()
{
    return CloseAllChildWindows();
}

/////////////////////////////////////////////////////////////////////////
void CMainFrame::OnFileNew()
{
    BOOL bMaximized = FALSE;
    // creates a new child window, maximized if active child is maximized
    CChildFrame* pActiveChild = (CChildFrame*) MDIGetActive(&bMaximized);
    new CChildFrame(bMaximized);
}

/////////////////////////////////////////////////////////////////////////
void CMainFrame::OnWindowCloseAll()
{
    CloseAllChildWindows();
}

/////////////////////////////////////////////////////////////////////////
void CMainFrame::OnUpdateWindowCloseAll(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(MDIGetActive() != NULL);
}

/////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::CloseAllChildWindows()
{
    // returns TRUE if all child windows permit closure
    CChildFrame* pChild;
    CChildFrame* pPrevChild = NULL;
    while ((pChild = (CChildFrame*) MDIGetActive()) != NULL) {
        if (pChild == pPrevChild)
            return FALSE; // closure not permitted
        pPrevChild = pChild;
        pChild->SendMessage(WM_CLOSE);
    }
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
    //{{AFX_MSG_MAP(CChildFrame)
    ON_WM_PAINT()
    ON_WM_CLOSE()
    ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

int NEAR CChildFrame::nChild = 1; // static

/////////////////////////////////////////////////////////////////////////
CChildFrame::CChildFrame(BOOL bMaximized /*= FALSE*/)
{
    char szTitle[30];
    wsprintf(szTitle, "EX22C Child Window %d", nChild++);
    CMainFrame* pFrameWnd = (CMainFrame*) AfxGetApp()->m_pMainWnd;
    Create(NULL, szTitle,
           WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW |
           (bMaximized ? WS_MAXIMIZE : 0),
           rectDefault, pFrameWnd);
}

/////////////////////////////////////////////////////////////////////////
void CChildFrame::OnPaint()
{
    CPaintDC dc(this);
    dc.TextOut(0, 0, "Hello, world!");
}

/////////////////////////////////////////////////////////////////////////
void CChildFrame::OnClose()
{
    if(AfxMessageBox("OK to close window?", MB_YESNO) == IDYES) { 
        CMDIChildWnd::OnClose();
    }
}

/////////////////////////////////////////////////////////////////////////
void CChildFrame::OnFileClose()
{
    SendMessage(WM_CLOSE);
}
