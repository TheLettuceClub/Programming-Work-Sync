// ex11adlg.cpp : implementation file
//

#include "stdafx.h"
#include "ex11a.h"
#include "ex11adlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx11aDialog dialog

CEx11aDialog::CEx11aDialog(CWnd* pParent /*=NULL*/)
    : CDialog(CEx11aDialog::IDD, pParent)
{
    //{{AFX_DATA_INIT(CEx11aDialog)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}

void CEx11aDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CEx11aDialog)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEx11aDialog, CDialog)
    //{{AFX_MSG_MAP(CEx11aDialog)
    ON_BN_CLICKED(IDC_EDIT_COPY, OnEditCopy)
    ON_BN_CLICKED(IDC_EDIT_CUT, OnEditCut)
    ON_BN_CLICKED(IDC_EDIT_PASTE, OnEditPaste)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx11aDialog message handlers


BOOL CEx11aDialog::OnInitDialog()
{
    VERIFY(m_editPaste.AutoLoad(IDC_EDIT_PASTE, this));
    VERIFY(m_editCut.AutoLoad(IDC_EDIT_CUT, this));
    VERIFY(m_editCopy.AutoLoad(IDC_EDIT_COPY, this));
    m_nButton = 0;
    return CDialog::OnInitDialog();
}

void CEx11aDialog::OnEditCopy()
{
    SetDlgItemText(IDC_MESSAGE, "Copy");
    m_nButton = 1;
}

void CEx11aDialog::OnEditCut()
{
    SetDlgItemText(IDC_MESSAGE, "Cut");
    m_nButton = 2;
}

void CEx11aDialog::OnEditPaste()
{
    SetDlgItemText(IDC_MESSAGE, "Paste");
    m_nButton = 3;
}
