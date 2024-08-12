// ex11cdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEx11cDialog dialog

class CEx11cDialog : public CDialog
{
// Construction
public:
	CEx11cDialog(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CEx11cDialog)
	enum { IDD = IDD_DIALOG1 };
	CVBControl*	m_pVBCntr;
	float	m_fCntrValue;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CEx11cDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
