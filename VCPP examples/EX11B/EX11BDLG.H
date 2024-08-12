// ex11bdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEx11bDialog dialog

class CEx11bDialog : public CDialog
{
private:
    long m_lCount;
    static const long lMaxCount;
// Construction
public:
    CEx11bDialog(CWnd* pParent = NULL); // standard constructor

// Dialog Data
    //{{AFX_DATA(CEx11bDialog)
    enum { IDD = IDD_DIALOG1 };
        // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA

// Implementation
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Generated message map functions
    //{{AFX_MSG(CEx11bDialog)
    afx_msg void OnTimer(UINT nIDEvent);
    virtual void OnCancel();
    afx_msg void OnStart();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
