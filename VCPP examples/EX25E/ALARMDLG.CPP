// alarmdlg.cpp : implementation file
//

#include "stdafx.h"
#include "ex25e.h"
#include "alarmdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlarmDialog dialog


CAlarmDialog::CAlarmDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CAlarmDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAlarmDialog)
	m_hours = 0;
	m_minutes = 0;
	m_seconds = 0;
	//}}AFX_DATA_INIT
}

void CAlarmDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAlarmDialog)
	DDX_Text(pDX, IDC_HRS, m_hours);
	DDV_MinMaxInt(pDX, m_hours, 0, 23);
	DDX_Text(pDX, IDC_MINS, m_minutes);
	DDV_MinMaxInt(pDX, m_minutes, 0, 59);
	DDX_Text(pDX, IDC_SECS, m_seconds);
	DDV_MinMaxInt(pDX, m_seconds, 0, 59);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAlarmDialog, CDialog)
	//{{AFX_MSG_MAP(CAlarmDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CAlarmDialog message handlers
