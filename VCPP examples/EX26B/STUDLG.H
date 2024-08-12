// studlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStudentDialog dialog

class CStudentDialog : public CDialog
{
private:
	int m_nDefButton;
// Construction
public:
	CStudentDialog(int nDefButton, CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CStudentDialog)
	enum { IDD = IDD_STUDENT };
	CString	m_name;
	long	m_lGrade;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual void OnOK();
	virtual void OnCancel();

	// Generated message map functions
	//{{AFX_MSG(CStudentDialog)
	afx_msg void OnClickedCancel();
	afx_msg void OnClickedClear();
	afx_msg void OnClickedDelete();
	afx_msg void OnClickedInsert();
	afx_msg void OnClickedUpdate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
