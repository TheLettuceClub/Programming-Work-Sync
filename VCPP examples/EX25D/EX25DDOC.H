// ex25ddoc.h : interface of the CEx25dDoc class
//
/////////////////////////////////////////////////////////////////////////////
#include "cvariant.h"
class CAlarm;
class CEx25dDoc : public CDocument
{
protected: // create from serialization only
	CEx25dDoc();
	DECLARE_DYNCREATE(CEx25dDoc)

// Implementation
public:
	virtual ~CEx25dDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual BOOL OnNewDocument();
	virtual void OnFinalRelease();     // debug purposes only

// Generated message map functions
protected:
	//{{AFX_MSG(CEx25dDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	// m_time out of ClassWizard's sight because it is CVariant, not VARIANT
	CVariant m_time;
    CString m_figure[4];
	CAlarm* m_pAlarm;
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CEx25dDoc)
	afx_msg void Refresh();
	afx_msg void ShowWin();
	afx_msg LPDISPATCH CreateAlarm(const VARIANT FAR& time);
	//}}AFX_DISPATCH
	// outside of ClassWizard's view because they use 
	afx_msg CVariant GetFigure(short n);
	afx_msg void SetFigure(short n, const VARIANT FAR& vNew);
	DECLARE_DISPATCH_MAP()
};

/////////////////////////////////////////////////////////////////////////////
