// mainfrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
    CMainFrame();
    DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Implementation
public:
    virtual ~CMainFrame();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
    CStatusBar  m_wndStatusBar;
    CToolBar    m_wndToolBar;

// Generated message map functions
protected:
    //{{AFX_MSG(CMainFrame)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnViewStatusBar();
    afx_msg void OnUpdateViewStatusBar(CCmdUI* pCmdUI);
    //}}AFX_MSG
    afx_msg void OnUpdateKeyShift(CCmdUI* pCmdUI);
    afx_msg void OnUpdateKeyCtrl(CCmdUI* pCmdUI);
    afx_msg void OnUpdateKeyAlt(CCmdUI* pCmdUI);
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
