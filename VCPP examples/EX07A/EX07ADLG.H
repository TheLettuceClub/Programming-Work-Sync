// ex07adlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEx07aDialog dialog

class CEx07aDialog : public CDialog
{
public:
    CView* m_pView;
// Construction
public:
    CEx07aDialog(CWnd* pParent = NULL); // standard constructor
    CEx07aDialog(CView* pView);
    BOOL Create();

// Dialog Data
    //{{AFX_DATA(CEx07aDialog)
    enum { IDD = IDD_DIALOG1 };
    CString m_edit1;
    //}}AFX_DATA

// Implementation
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Generated message map functions
    //{{AFX_MSG(CEx07aDialog)
    virtual void OnCancel();
    virtual void OnOK();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
