// ex07bvw.h : interface of the CEx07bView class
//
/////////////////////////////////////////////////////////////////////////////

class CEx07bView : public CView
{
protected: // create from serialization only
	CEx07bView();
	DECLARE_DYNCREATE(CEx07bView)

// Attributes
public:
	CEx07bDoc* GetDocument();

// Operations
public:

// Implementation
public:
	virtual ~CEx07bView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// Generated message map functions
protected:
	//{{AFX_MSG(CEx07bView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG	// debug version in ex07bvw.cpp
inline CEx07bDoc* CEx07bView::GetDocument()
   { return (CEx07bDoc*) m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
