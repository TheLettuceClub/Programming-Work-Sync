// ex07adlg.cpp : implementation file
//

#include "stdafx.h"
#include "ex07a.h"
#include "ex07adlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx07aDialog dialog

CEx07aDialog::CEx07aDialog(CWnd* pParent /*=NULL*/)
    : CDialog(CEx07aDialog::IDD, pParent)
{
    //{{AFX_DATA_INIT(CEx07aDialog)
    m_edit1 = "";
    //}}AFX_DATA_INIT
    m_pView = NULL;
}

CEx07aDialog::CEx07aDialog(CView* pView) // modeless constructor
    : CDialog()
{
    m_pView = pView;
}


BOOL CEx07aDialog::Create()
{
    return CDialog::Create(CEx07aDialog::IDD);
}

void CEx07aDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CEx07aDialog)
    DDX_Text(pDX, IDC_EDIT1, m_edit1);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEx07aDialog, CDialog)
    //{{AFX_MSG_MAP(CEx07aDialog)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx07aDialog message handlers

void CEx07aDialog::OnCancel()
{   // Do not call base class OnOk
    CDialog::OnCancel();
    if (m_pView != NULL) {
      m_pView->PostMessage(WM_GOODBYE, IDCANCEL);
    }
}

void CEx07aDialog::OnOK()
{   // Do not call base class OnCancel
    CDialog::OnOK();
    if (m_pView != NULL) {
      m_pView->PostMessage(WM_GOODBYE, IDOK);
    }
}
