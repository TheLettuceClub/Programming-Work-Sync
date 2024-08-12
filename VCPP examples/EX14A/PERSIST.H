// persist.h : CPersistentView class declaration
//

class CPersistentFrame : public CFrameWnd
{ // remembers where it was on the desktop
    DECLARE_DYNAMIC(CPersistentFrame)
private:
    static const CRect NEAR rectDefault;
    CString m_profileHeading, m_profileRect, m_profileIcon;
    CString m_profileMax, m_profileTool, m_profileStatus;
    BOOL    m_bFirstTime;
protected: // create from serialization only
    CPersistentFrame();
    ~CPersistentFrame();
    virtual void ActivateFrame(int nCmdShow = -1);
    //{{AFX_MSG(CPersistentFrame)
    afx_msg void OnDestroy();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
