// application class
#include "resource.h"

class CEx22aApp : public CWinApp
{
public:
    virtual BOOL InitInstance();
};

// frame window class
class CMainFrame : public CFrameWnd
{
public:
    CMainFrame();
protected:  
    //{{AFX_MSG(CMainFrame)
    afx_msg void OnPaint();
    afx_msg void OnClose();
    afx_msg BOOL OnQueryEndSession();
    afx_msg void OnFile();
    afx_msg void OnHlp();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
