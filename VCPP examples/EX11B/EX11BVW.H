// ex11bvw.h : interface of the CEx11bView class
//
/////////////////////////////////////////////////////////////////////////////

class CEx11bView : public CView
{
protected: // create from serialization only
	CEx11bView();
	DECLARE_DYNCREATE(CEx11bView)

// Attributes
public:
	CEx11bDoc* GetDocument();

// Operations
public:

// Implementation
public:
	virtual ~CEx11bView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// Generated message map functions
protected:
	//{{AFX_MSG(CEx11bView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG	// debug version in ex11bvw.cpp
inline CEx11bDoc* CEx11bView::GetDocument()
   { return (CEx11bDoc*) m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
