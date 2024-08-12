// ex11adlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEx11aDialog dialog

class CEx11aDialog : public CDialog
{
friend class CEx11aView;
private:
    CBitmapButton m_editCopy;
    CBitmapButton m_editCut;
    CBitmapButton m_editPaste;
    int m_nButton; // 1=copy, 2=cut, 3=paste, 0=none
// Construction
public:
    CEx11aDialog(CWnd* pParent = NULL); // standard constructor

// Dialog Data
    //{{AFX_DATA(CEx11aDialog)
    enum { IDD = IDD_BITMAP };
        // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA

// Implementation
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Generated message map functions
    //{{AFX_MSG(CEx11aDialog)
    virtual BOOL OnInitDialog();
    afx_msg void OnEditCopy();
    afx_msg void OnEditCut();
    afx_msg void OnEditPaste();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
