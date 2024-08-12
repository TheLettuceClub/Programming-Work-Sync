// matdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMatplanDialog dialog

class CMatplanDialog : public CDialog
{
private:
    CPiece* m_pPiece;
// Construction
public:
    CMatplanDialog(CWnd* pParentWnd, CPiece* pPiece);

// Dialog Data
    //{{AFX_DATA(CMatplanDialog)
        enum { IDD = IDD_FORM };
        // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA

// Implementation
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual void OnCancel();

    // Generated message map functions
    //{{AFX_MSG(CMatplanDialog)
    afx_msg void OnClickedCancel();
    afx_msg void OnClear();
    afx_msg void OnDelete();
    afx_msg void OnInsert();
    afx_msg void OnUpdate();
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

