// ex11avw.h : interface of the CEx11aView class
//
/////////////////////////////////////////////////////////////////////////////

class CEx11aView : public CView
{
protected: // create from serialization only
	CEx11aView();
	DECLARE_DYNCREATE(CEx11aView)

// Attributes
public:
	CEx11aDoc* GetDocument();

// Operations
public:

// Implementation
public:                      
	virtual ~CEx11aView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Printing support
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Generated message map functions
protected:
	//{{AFX_MSG(CEx11aView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG	// debug version in ex11avw.cpp
inline CEx11aDoc* CEx11aView::GetDocument()
   { return (CEx11aDoc*) m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
