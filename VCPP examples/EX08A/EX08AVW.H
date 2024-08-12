// ex08avw.h : interface of the CEx08aView class
//
/////////////////////////////////////////////////////////////////////////////

class CEx08aView : public CView
{
protected: // create from serialization only
	CEx08aView();
	DECLARE_DYNCREATE(CEx08aView)

// Attributes
public:
	CEx08aDoc* GetDocument();

// Operations
public:

// Implementation
public:
	virtual ~CEx08aView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// Generated message map functions
protected:
	//{{AFX_MSG(CEx08aView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG	// debug version in ex08avw.cpp
inline CEx08aDoc* CEx08aView::GetDocument()
   { return (CEx08aDoc*) m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
