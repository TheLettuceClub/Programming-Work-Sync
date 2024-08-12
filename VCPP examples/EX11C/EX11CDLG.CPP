// ex11cdlg.cpp : implementation file
//

#include "stdafx.h"
#include "ex11c.h"
#include "ex11cdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx11cDialog dialog

CEx11cDialog::CEx11cDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CEx11cDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEx11cDialog)
	m_pVBCntr = NULL;
	m_fCntrValue = 0;
	//}}AFX_DATA_INIT
}

void CEx11cDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEx11cDialog)
	DDX_VBControl(pDX, IDC_COUNTER1, m_pVBCntr);
	DDX_VBFloat(pDX, IDC_COUNTER1, 19, m_fCntrValue);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEx11cDialog, CDialog)
	//{{AFX_MSG_MAP(CEx11cDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx11cDialog message handlers
