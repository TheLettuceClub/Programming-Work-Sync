#include "resource.h"

class CEx22cApp : public CWinApp
{
public:
    virtual BOOL InitInstance();
};

// MDI frame window class
class CMainFrame : public CMDIFrameWnd
{
public:
    CMainFrame();
protected:
    //{{AFX_MSG(CMainFrame)
    afx_msg void OnFileNew();
    afx_msg void OnWindowCloseAll();
    afx_msg void OnUpdateWindowCloseAll(CCmdUI* pCmdUI);
    afx_msg void OnClose();
    afx_msg BOOL OnQueryEndSession();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
protected:
    BOOL CloseAllChildWindows();
};

// MDI child frame window class
class CChildFrame : public CMDIChildWnd
{
public:
    static int NEAR nChild;
    CChildFrame(BOOL bMaximized = FALSE);
protected:
    //{{AFX_MSG(CChildFrame)
    afx_msg void OnPaint();
    afx_msg void OnFileClose();
    afx_msg void OnClose();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
