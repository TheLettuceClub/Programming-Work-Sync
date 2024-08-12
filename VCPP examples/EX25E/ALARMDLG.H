// alarmdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAlarmDialog dialog

class CAlarmDialog : public CDialog
{
// Construction
public:
	CAlarmDialog(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAlarmDialog)
	enum { IDD = IDD_ALARMDIALOG };
	int		m_hours;
	int		m_minutes;
	int		m_seconds;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CAlarmDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
