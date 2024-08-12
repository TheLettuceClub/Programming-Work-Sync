// ex13bvw.h : interface of the CEx13bView class
//
/////////////////////////////////////////////////////////////////////////////

class CEx13bView : public CView
{
protected: // create from serialization only
	CEx13bView();
	DECLARE_DYNCREATE(CEx13bView)

// Attributes
public:
	CEx13bDoc* GetDocument();

// Operations
public:

// Implementation
public:
	virtual ~CEx13bView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx13bView)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex13bvw.cpp
inline CEx13bDoc* CEx13bView::GetDocument()
   { return (CEx13bDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
