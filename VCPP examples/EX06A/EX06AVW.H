// ex06avw.h : interface of the CEx06aView class
//
/////////////////////////////////////////////////////////////////////////////

class CEx06aView : public CView
{
protected: // create from serialization only
	CEx06aView();
	DECLARE_DYNCREATE(CEx06aView)

// Attributes
public:
	CEx06aDoc* GetDocument();

// Operations
public:

// Implementation
public:
	virtual ~CEx06aView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// Generated message map functions
protected:
	//{{AFX_MSG(CEx06aView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG	// debug version in ex06avw.cpp
inline CEx06aDoc* CEx06aView::GetDocument()
   { return (CEx06aDoc*) m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
