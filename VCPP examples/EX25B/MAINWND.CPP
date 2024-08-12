// mainwnd.cpp

#include "stdafx.h"
#include "ex25b.h"

/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CMainWnd, CFrameWnd)
    //{{AFX_MSG_MAP(CMainWnd)
    ON_WM_CLOSE()
    ON_COMMAND(IDM_UPDATE, OnUpdateClient)
    ON_COMMAND(IDM_ABOUT, OnAbout)
    ON_COMMAND(IDM_EXIT, OnExit)
    ON_WM_SIZE()
    ON_WM_CREATE()
    ON_EN_CHANGE(1, OnEditChange)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Basic creation etc

// Disable excessive compiler warning
#pragma warning(disable:4355)   // 'this' used in constructor

CMainWnd::CMainWnd() : m_server(this)
{
    Create(NULL, SERVER_LOCAL_NAME, WS_OVERLAPPEDWINDOW,
           CRect(0, 200, 200, 400), NULL,
           MAKEINTRESOURCE(IDR_MAINFRAME));
}

/////////////////////////////////////////////////////////////////////////////
int CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    CRect rect;
    
    if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
        return -1;
    GetClientRect(rect);
    m_wndEdit.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL |
                     ES_MULTILINE | ES_AUTOVSCROLL, rect,
                     this, 1);          
    return 0;
}

/////////////////////////////////////////////////////////////////////////////
void CMainWnd::OnSize(UINT nType, int cx, int cy)
{
    CRect rect;
    // makes the edit control size track the main window size
    GetClientRect(rect);
    m_wndEdit.SetWindowPos(&wndTop, 0, 0, rect.Width(), rect.Height(),
                           SWP_SHOWWINDOW);
}

/////////////////////////////////////////////////////////////////////////////
// Update Client
void CMainWnd::OnUpdateClient()
{
    TRACE("Entering CMainWnd::OnUpdateClient\n");
    m_server.m_doc.m_item.m_bModified = FALSE;
    m_wndEdit.GetWindowText(m_server.m_doc.m_item.m_noteText);
    TRY {
        m_server.m_doc.NotifySaved();
    }
    CATCH (CException, e) {
        AfxMessageBox("Could not update client");
    }
    END_CATCH
}

/////////////////////////////////////////////////////////////////////////////
void CMainWnd::OnClose()
{
    if (m_server.m_doc.m_item.m_bModified == TRUE) {
        if (AfxMessageBox("Do you want to update the client?",
                           MB_YESNO) == IDYES) {
            OnUpdateClient();
        }
    }
    OnExit();
}

/////////////////////////////////////////////////////////////////////////////
void CMainWnd::OnExit()
{
    m_server.BeginRevoke();
}

/////////////////////////////////////////////////////////////////////////////
// Help menu commands
void CMainWnd::OnAbout()
{
    CDialog(IDD_ABOUTBOX).DoModal();
}

/////////////////////////////////////////////////////////////////////////////
void CMainWnd::OnEditChange()
{
    m_server.m_doc.m_item.m_bModified = TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CReadDialog dialog class
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CReadDialog, CDialog)
    //{{AFX_MSG_MAP(CReadDialog)
    ON_WM_CTLCOLOR()
    ON_WM_DESTROY()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
CReadDialog::CReadDialog(CEx25bItem* pItem, CWnd* pParent /*=NULL*/)
    : CDialog(CReadDialog::IDD, pParent)
{
    m_pItem = pItem;
}

/////////////////////////////////////////////////////////////////////////////
BOOL CReadDialog::OnInitDialog()
{
    SetDlgItemText(IDC_EDIT1, m_pItem->m_noteText);
    m_hBrush = ::CreateSolidBrush(RGB(255, 255, 0)); // yellow
    return TRUE;
}
 
/////////////////////////////////////////////////////////////////////////////
HBRUSH CReadDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    // sets edit control's background color
    TRACE("Entering CReadDialog::OnCtlColor\n");
    if (nCtlColor == CTLCOLOR_EDIT) {
        pDC->SetBkColor(RGB(255, 255, 0)); // yellow
        return m_hBrush;
    }
    return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}

/////////////////////////////////////////////////////////////////////////////
void CReadDialog::OnDestroy()
{
    CDialog::OnDestroy();
    VERIFY(::DeleteObject(m_hBrush));
}
