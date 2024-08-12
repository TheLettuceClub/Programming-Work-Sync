// ex11bdlg.cpp : implementation file
//

#include "stdafx.h"
#include "ex11b.h"
#include "ex11bdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

const long NEAR CEx11bDialog::lMaxCount = 500L;

/////////////////////////////////////////////////////////////////////////////
// CEx11bDialog dialog

CEx11bDialog::CEx11bDialog(CWnd* pParent /*=NULL*/)
    : CDialog(CEx11bDialog::IDD, pParent)
{
    m_lCount = 0L;
    //{{AFX_DATA_INIT(CEx11bDialog)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}

void CEx11bDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CEx11bDialog)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEx11bDialog, CDialog)
    //{{AFX_MSG_MAP(CEx11bDialog)
    ON_WM_TIMER()
    ON_BN_CLICKED(IDC_START, OnStart)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx11bDialog message handlers

void CEx11bDialog::OnTimer(UINT nIDEvent)
{
    CScrollBar* pBar = (CScrollBar*) GetDlgItem(IDC_SCROLLBAR1);
    pBar->SetScrollRange(0, (int) lMaxCount);
    pBar->SetScrollPos((int) m_lCount);
}

void CEx11bDialog::OnCancel()
{
    TRACE("Entering CEx11bDialog::OnCancel\n");
    if (m_lCount == 0L) {    // prior to Start button
      CDialog::OnCancel();
    }
    else { // computation in progress
      m_lCount = lMaxCount;  // force exit from OnClickedButton1
    }
}

void CEx11bDialog::OnStart()
{
    MSG Message;
    int nTemp;
    int nTimer;

    nTimer = SetTimer(1, 100, NULL); // 1/10 second
    ASSERT(nTimer != 0);
    GetDlgItem(IDC_START)->EnableWindow(FALSE);
    for (m_lCount = 0L; m_lCount < lMaxCount; m_lCount++) {
      for (nTemp = 0; nTemp < 30000; nTemp++) {} // simulate computation
      if (::PeekMessage(&Message, NULL, 0, 0, PM_REMOVE)) {
        ::TranslateMessage(&Message);
        ::DispatchMessage(&Message);
      }
    }
    KillTimer(nTimer);
    CDialog::OnOK();
}
