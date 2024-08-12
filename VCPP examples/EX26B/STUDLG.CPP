// studlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "studlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStudentDialog dialog

BEGIN_MESSAGE_MAP(CStudentDialog, CDialog)
	//{{AFX_MSG_MAP(CStudentDialog)
	ON_BN_CLICKED(IDB_CANCEL, OnClickedCancel)
	ON_BN_CLICKED(IDB_CLEAR, OnClickedClear)
	ON_BN_CLICKED(IDB_DELETE, OnClickedDelete)
	ON_BN_CLICKED(IDB_INSERT, OnClickedInsert)
	ON_BN_CLICKED(IDB_UPDATE, OnClickedUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
CStudentDialog::CStudentDialog(int nDefButton, CWnd* pParent /*=NULL*/)
	: CDialog(CStudentDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStudentDialog)
	m_nDefButton = nDefButton;
	m_lGrade = 0;
	//}}AFX_DATA_INIT
}

/////////////////////////////////////////////////////////////////////////////
void CStudentDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStudentDialog)
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDV_MaxChars(pDX, m_name, 20);
	DDX_Text(pDX, IDC_EDIT2, m_lGrade);
	DDV_MinMaxLong(pDX, m_lGrade, 0, 100);
	//}}AFX_DATA_MAP
	SetDefID(m_nDefButton); // Insert or Update
	}

/////////////////////////////////////////////////////////////////////////////
void CStudentDialog::OnOK() // system menu close
{
	EndDialog(IDB_CANCEL);
}

/////////////////////////////////////////////////////////////////////////////
void CStudentDialog::OnCancel() // Esc key
{
	EndDialog(IDB_CANCEL);
}

/////////////////////////////////////////////////////////////////////////////
// CStudentDialog message handlers

void CStudentDialog::OnClickedCancel()
{
	EndDialog(IDB_CANCEL);
}

/////////////////////////////////////////////////////////////////////////////
void CStudentDialog::OnClickedClear()
{
	m_name = "";
	m_lGrade = 0L;
	UpdateData(FALSE);
	SetDefID(IDB_INSERT); // insert is the next logical operation
	GotoDlgCtrl(GetDlgItem(IDC_EDIT1));
}

/////////////////////////////////////////////////////////////////////////////
void CStudentDialog::OnClickedDelete()
{
	EndDialog(IDB_DELETE);
}

/////////////////////////////////////////////////////////////////////////////
void CStudentDialog::OnClickedInsert()
{
	if(!UpdateData(TRUE)) return;
	EndDialog(IDB_INSERT);
}

/////////////////////////////////////////////////////////////////////////////
void CStudentDialog::OnClickedUpdate()
{
	if(!UpdateData(TRUE)) return;
	EndDialog(IDB_UPDATE);
}
