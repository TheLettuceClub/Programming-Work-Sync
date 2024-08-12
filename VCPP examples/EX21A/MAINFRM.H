// mainfrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __AFXEXT_H__
#include <afxext.h>			// for access to CToolBar and CStatusBar
#endif

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif


protected:	// control bar embedded members
	CStatusBar	m_wndStatusBar;
	CToolBar	m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnWindowNewList();
		afx_msg void OnWindowNewPlan();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
class CMDISpecialChildWnd: public CMDIChildWnd
{
	DECLARE_DYNCREATE(CMDISpecialChildWnd)
public:
	CMDISpecialChildWnd();
	LRESULT OnCommandHelp(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};
