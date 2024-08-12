// mainfrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ex13b.h"

#include "mainfrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
    //{{AFX_MSG_MAP(CMainFrame)
    ON_WM_CREATE()
    ON_COMMAND(ID_VIEW_STATUS_BAR, OnViewStatusBar)
    ON_UPDATE_COMMAND_UI(ID_VIEW_STATUS_BAR, OnUpdateViewStatusBar)
    //}}AFX_MSG_MAP
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_SHIFT, OnUpdateKeyShift)
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_CTRL, OnUpdateKeyCtrl)
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_ALT, OnUpdateKeyAlt)
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
};

static UINT BASED_CODE indicators[] =
{
    ID_SEPARATOR,  // first message line pane
    ID_SEPARATOR,  // second message line pane
    ID_INDICATOR_SHIFT,
    ID_INDICATOR_CTRL,
    ID_INDICATOR_ALT,
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
    if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    if (!m_wndToolBar.Create(this) ||
        !m_wndToolBar.LoadBitmap(IDR_MAINFRAME) ||
        !m_wndToolBar.SetButtons(buttons,
          sizeof(buttons)/sizeof(UINT)))
    {
        TRACE("Failed to create toolbar\n");
        return -1;      // fail to create
    }

    if (!m_wndStatusBar.Create(this,
        WS_CHILD | WS_VISIBLE | CBRS_BOTTOM, ID_MY_STATUS_BAR) ||
        !m_wndStatusBar.SetIndicators(indicators,
          sizeof(indicators)/sizeof(UINT)))
    {
        TRACE("Failed to create status bar\n");
        return -1;      // fail to create
    }

    return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
    CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
    CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
void CMainFrame::OnUpdateKeyShift(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(::GetKeyState(VK_SHIFT) < 0);
}

void CMainFrame::OnUpdateKeyCtrl(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(::GetKeyState(VK_CONTROL) < 0);
}

void CMainFrame::OnUpdateKeyAlt(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(::GetKeyState(VK_MENU) < 0);
}

void CMainFrame::OnViewStatusBar()
{
    CWnd* pBar;

    if (pBar = GetDescendantWindow(ID_MY_STATUS_BAR)) {
      // toggle visible state
      pBar->ShowWindow((pBar->GetStyle() & WS_VISIBLE) == 0);
      RecalcLayout();
    }
}

void CMainFrame::OnUpdateViewStatusBar(CCmdUI* pCmdUI)
{
    CWnd* pBar;
    if (pBar = GetDescendantWindow(ID_MY_STATUS_BAR)) {
      pCmdUI->SetCheck((pBar->GetStyle() & WS_VISIBLE) != 0);
    }
}
