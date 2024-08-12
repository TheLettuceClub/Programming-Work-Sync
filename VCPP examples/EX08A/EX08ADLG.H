// ex08adlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEx08aDialog dialog

class CEx08aDialog : public CDialog
{
// Construction
public:
    CEx08aDialog(CWnd* pParent = NULL); // standard constructor

// Dialog Data   
    double m_dArray[8][12];
    //{{AFX_DATA(CEx08aDialog)
    enum { IDD = IDD_DIALOG1 };
    CVBControl* m_pVBGrid;
    CString m_cellValue;
    //}}AFX_DATA

// Implementation
private:
    void ComputeSums();
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Generated message map functions
    //{{AFX_MSG(CEx08aDialog)
    afx_msg void OnSelchangeGrid1(UINT, int, CWnd*, LPVOID);
    virtual void OnCancel();
    virtual void OnOK();
    virtual BOOL OnInitDialog();
	afx_msg void OnAddrow();
	afx_msg void OnDeleterow();
	afx_msg void OnUpdatevalue();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
