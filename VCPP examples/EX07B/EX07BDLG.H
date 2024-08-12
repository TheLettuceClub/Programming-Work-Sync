// ex07bdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEx07bDialog dialog

class CEx07bDialog : public CFileDialog
{
// Construction
public:
	CEx07bDialog(CWnd* pParent = NULL);	// standard constructor

public:
    CButton m_deleteButton;
    BOOL    m_bDeleteFlag;

// Implementation
protected:
    virtual BOOL OnInitDialog();
    afx_msg void OnDeleteButton();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CEx07bDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
