// prompt.h
// Dialog class

class CPromptDlg : public CDialog
{
public:
	CPromptDlg(CWnd* pParent = NULL);

	//{{AFX_DATA(CPromptDlg)
	enum { IDD = IDD_PROMPT };
	long	m_longData;
	CString	m_strTextData;
	//}}AFX_DATA
	virtual void DoDataExchange(CDataExchange* pDX);
	//{{AFX_MSG(CPromptDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
