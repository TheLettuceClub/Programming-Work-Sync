// ex06adlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEx06aDialog dialog

class CEx06aDialog : public CDialog
{
    enum{ nMin = 0 };
    enum{ nMax = 100 };
    
// Construction
public:
    CEx06aDialog(CWnd* pParent = NULL); // standard constructor

// Dialog Data
    //{{AFX_DATA(CEx06aDialog)
    enum { IDD = IDD_DIALOG1 };
    CString m_name;
    CString m_bio;
    int     m_nCat;
    BOOL    m_bInsDis;
    CString m_dept;
    CString m_educ;
    BOOL    m_bInsLife;
    BOOL    m_bInsMed;
    CString m_lang;
    CString m_skill;
    long    m_lSsn;
    //}}AFX_DATA
public:
    int m_nLoyal;
    int m_nRely;

// Implementation
protected:
    virtual void OnOK();
    BOOL OnInitDialog();
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Generated message map functions
    //{{AFX_MSG(CEx06aDialog)
    afx_msg void OnClickedOk();
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnSpecial();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
