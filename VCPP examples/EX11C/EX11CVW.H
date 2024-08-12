// ex11cvw.h : interface of the CEx11cView class
//
/////////////////////////////////////////////////////////////////////////////

class CEx11cView : public CView
{
protected: // create from serialization only
	CEx11cView();
	DECLARE_DYNCREATE(CEx11cView)

// Attributes
public:
	CEx11cDoc* GetDocument();

// Operations
public:

// Implementation
public:
	virtual ~CEx11cView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// Generated message map functions
protected:
	//{{AFX_MSG(CEx11cView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG	// debug version in ex11cvw.cpp
inline CEx11cDoc* CEx11cView::GetDocument()
   { return (CEx11cDoc*) m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
