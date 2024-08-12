#include "resource.h"
class CEx22bDialog : public CDialog
{
public:
    CEx22bDialog();

// Dialog Data
    //{{AFX_DATA(CEx22bDialog)
    enum { IDD = IDD_EX22BDLG };
    double  m_d1;
    double  m_d2;
    double  m_d3;
    int     m_nOpr;
    //}}AFX_DATA

// Implementation
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //{{AFX_MSG(CEx22bDialog)
    afx_msg void OnCompute();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

class CEx22bApp : public CWinApp
{
private:
    CEx22bDialog m_dialog;
public:
    BOOL InitInstance();
};

