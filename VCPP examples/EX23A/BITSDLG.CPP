// bitsdlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "bitsdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBitsDialog dialog

CBitsDialog::CBitsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CBitsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBitsDialog)
	m_nBits = -1;
	m_bCompression = FALSE;
	//}}AFX_DATA_INIT
}

void CBitsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBitsDialog)
	DDX_Radio(pDX, IDC_BITS1, m_nBits);
	DDX_Check(pDX, IDC_COMPRESSION, m_bCompression);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBitsDialog, CDialog)
	//{{AFX_MSG_MAP(CBitsDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBitsDialog message handlers
