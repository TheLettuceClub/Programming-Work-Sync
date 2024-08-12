// ex04cvw.h : interface of the CEx04cView class
//
/////////////////////////////////////////////////////////////////////////////

class CEx04cView : public CScrollView
{
protected: // create from serialization only
	CEx04cView();
	DECLARE_DYNCREATE(CEx04cView)

// Attributes
public:
	CEx04cDoc* GetDocument();

// Operations
public:

// Implementation
public:
	virtual ~CEx04cView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Generated message map functions
protected:
	//{{AFX_MSG(CEx04cView)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex04cvw.cpp
inline CEx04cDoc* CEx04cView::GetDocument()
   { return (CEx04cDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
