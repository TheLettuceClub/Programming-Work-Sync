// ex07bdlg.cpp : implementation file
//

#include "stdafx.h"
#include "ex07b.h"
#include "ex07bdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx07bDialog dialog

CEx07bDialog::CEx07bDialog(CWnd* pParent /*=NULL*/)
    : CFileDialog(TRUE, NULL, "*.*")
{
    m_ofn.lpstrTitle = "File Delete"; // dialog caption
}

BOOL CEx07bDialog::OnInitDialog()
{
    m_bDeleteFlag = FALSE;
    CRect rect; // button location in dialog window
    CWnd* pWndCancel = GetDlgItem(IDCANCEL);  // look at the Cancel button
    pWndCancel->GetWindowRect(&rect);         // get its size and position
    int nDiff = (rect.bottom - rect.top) * 2; // Move down from it
    rect.top += nDiff;                        // delete button's top...
    rect.bottom += nDiff;                     //  ...and bottom
    ScreenToClient (rect);                    // convert back to dialog
    CFont* pFont = pWndCancel->GetFont();     // get Cancel button's font
            
    m_deleteButton.Create("Delete",
                           WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                           rect, this, IDC_DELETE);
    GetDlgItem(IDC_DELETE)->SetFont(pFont, TRUE);   // set up font
    SetDlgItemText(IDOK, "Open");                   // change OK button's
                                                    //  caption
    return CFileDialog::OnInitDialog();
}


void CEx07bDialog::OnDeleteButton()
{
    m_bDeleteFlag = TRUE;
    SendMessage(WM_COMMAND, IDOK, BN_CLICKED);
}


void CEx07bDialog::DoDataExchange(CDataExchange* pDX)
{
    CFileDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CEx07bDialog)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEx07bDialog, CFileDialog)
    //{{AFX_MSG_MAP(CEx07bDialog)
        // NOTE: the ClassWizard will add message map macros here
    ON_BN_CLICKED(IDC_DELETE, OnDeleteButton)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx07bDialog message handlers
