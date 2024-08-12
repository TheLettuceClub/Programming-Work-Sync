// bitsdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBitsDialog dialog

class CBitsDialog : public CDialog
{
// Construction
public:
	CBitsDialog(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBitsDialog)
	enum { IDD = IDD_BITS };
	int		m_nBits;
	BOOL	m_bCompression;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CBitsDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
